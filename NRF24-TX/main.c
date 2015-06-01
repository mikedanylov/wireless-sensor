/*
 * main.c
 *
 *  Created on: Jan 6, 2015
 *      Author: mikedanylov
 */
#define F_CPU 128000UL
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "NRF24L01/nrf24.h"
#include "TempSensHardAdapt.h"

/*
 * LEDs ports and pins
 *
 * LED_tx - blinks once when data is transmitted.
 * 			Also used for debugging purposes.
 * 			ATmega328p pin 11, PD5, DDRD, PORTD
 * LED_bat - (planned)red led, blinks 3 times
 * 			when battery level is low.
 */
#define LED_tx PD5
/*
 * Waiting time is calculated
 * considering Interrupt Frequency = 2.04 Hz
 *
 * For example, if WAIT_TIME = 10
 * will generate ~20.4s of waiting time
 */
#define WAIT_TIME 5

int TIMER_OVERFLOW = 0;
char* Temperature;
char buffer[PAYLOAD];
uint8_t tx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};

void timer2_init(){

    // set up timer with prescaler = 1024
    TCCR2B |= (1 << CS22);
    TCCR2B |= (1 << CS21);
	TCCR2B |= (1 << CS20);
    // initialize counter
    TCNT2 = 0;
    // enable overflow interrupt
    TIMSK2 |= (1 << TOIE2);
    // enable global interrupts
    sei();
}

void CPU_sleep(){

	cli();
	sleep_enable();
	sei();
	sleep_cpu();
	sleep_disable();
}

ISR(TIMER2_OVF_vect);

int main(){

	nrf24_init();
	timer2_init();
	// Make LED pin of PORTD an output
	DDRD = DDRD | (1<<LED_tx);
	// set sleep mode for the chip
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	/* Channel, payload length*/
	nrf24_config(NRF24_CH,PAYLOAD);
	/* Set the device addresses */
	nrf24_tx_address(tx_address);

	while(1){

		if (TIMER_OVERFLOW >= WAIT_TIME){

			cli(); // turn off interrupts
			TIMER_OVERFLOW = 0;
			// Set LED_tx high indicating that transmission started
			PORTD |= 1 << LED_tx;

			/* Get temperature from sensor
			 * return format: '23.45 C'
			 */
			Temperature = getTemperature();

			/* Automatically goes to TX mode */
			nrf24_send(Temperature);

			/* Wait for transmission to end */
			while(nrf24_isSending());
			_delay_ms(100);
			// Set LED_tx low indicating that transmission completed
			PORTD &= ~(1 << LED_tx);
		}
		// Put CPU to sleep mode
		CPU_sleep();
	}
}

// Interrupt Frequency = 2.04 Hz
ISR(TIMER2_OVF_vect){
	TIMER_OVERFLOW++;
}
