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
#include "NRF24L01_HardAdapt.h"
#include "Record.h"
#include "UART/uart.h"

/*
 * LEDs ports and pins
 *
 * LED_tx - blinks once when data is transmitted.
 * 			Also used for debugging purposes.
 * 			ATmega328p pin 11, PD5, DDRD, PORTD
 * LED_bat - (planned)red led, blinks 3 times
 * 			when battery level is low.
 */

#define LED_tx PD7
#define Trans_PIN PB1
#define UART_BAUD_RATE 26

/*
 * Waiting time is calculated
 * considering Interrupt Frequency = 2.04 Hz
 *
 * For example, if WAIT_TIME = 10
 * will generate ~20.4s of waiting time
 */

#define WAIT_TIME 5
int TIMER_OVERFLOW = 0;

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

//	uint8_t* Temperature;
//	uint8_t tx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
//	Record record;

	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
//	sei(); // needed after uart_init
	timer2_init();
//	transceiver_init();
//	transceiver_set_channel(2);
//	transceiver_set_payload(8);
//	transceiver_config();
//	transceiver_tx_address(tx_address);// Set the device addresses
//	record_set_sensor_id(&record, 1); // id should be unique for each sensor

	DDRD = DDRD | (1<<LED_tx);// Make LED pin of PORTD an output
	PORTD &= ~(1 << LED_tx);// Set LED_tx low

	DDRB = DDRB | (1<<Trans_PIN);// Make Transistor pin of PORTB an output
	PORTB |= 1 << Trans_PIN;// set pin high

	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	uart_puts("\r\nInitialization completed!\r\n\r\n");
	_delay_ms(1000);

	while(1){
		if (TIMER_OVERFLOW >= WAIT_TIME){

			uart_puts("Timer2 interrupt happened!\r\n");
			TIMER_OVERFLOW = 0; // reset interrupt counter

			PORTD |= 1 << LED_tx;// Set LED_tx high indicating that transmission has started
			PORTB &= ~(1 << Trans_PIN);// Set Transistor pin low, supplying power to transceiver and sensor
			_delay_ms(1000);
			/*
			 * TODO:
			 * 		1. Get data from sensor
			 * 		2. Convert to suitable data type for transmission
			 * 		3. Send data over wireless transceiver
			 */

			// 1. Get data from sensor



//			Temperature = sensor_get_temperature();// Get temperature from sensor: '23.45 C'
//			uart_puts("Hello!\n");
//			record_set_sensor_data(&record, Temperature);
//			transceiver_send(&record);// Automatically goes to TX mode

			PORTD &= ~(1 << LED_tx);// Set LED_tx low indicating that transmission has been completed
			PORTB |= 1 << Trans_PIN; // Set Transistor pin high cutting power off.
		}
		CPU_sleep();// Put CPU to sleep mode
	}
}

// Interrupt Frequency = 2.04 Hz
ISR(TIMER2_OVF_vect){
	TIMER_OVERFLOW++;
}
