/*
 * main.c
 *
 *  Created on: Jan 6, 2015
 *      Author: mikedanylov
 */
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <math.h>
#include "ADC.h"
#include "nrf24.h"
#include "hd44780.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define IDLE 000
#define LED PB1

double volatile Temperature;
char buffer[PAYLOAD];
uint8_t tx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
volatile int FLAG = 1;
volatile long counter = 0;

void timer1_init(){

	TIMSK1 |= (1 << TOIE1); // Enable overflow interrupt
	sei(); // Enable global interrupts
	TCCR1B |= (1 << CS12); // Start timer at Fcpu/256
}

void CPU_sleep(){

	cli();
	sleep_enable();
	sei();
	sleep_cpu();
	sleep_disable();
	sei();
}

ISR(TIMER1_OVF_vect);

int main(){

	nrf24_init();
	InitADC();
	lcd_init();
	timer1_init();

	/* Channel, payload length*/
	nrf24_config(NRF24_CH,PAYLOAD);

	/* Set the device addresses */
	nrf24_tx_address(tx_address);

	_delay_ms(1000);
	lcd_home();
	lcd_puts("Hello World");
	_delay_ms(1000);
	lcd_clrscr();

	while(1){

		if (FLAG == 1){

			// Blinking LED for debugging
			// Set pin 15 high.
			PORTB |= 1 << LED;
			_delay_ms(100);
			//PORTB ^= (1 << LED); // Toggle the LED
			// Set pin 15 low.
			PORTB &= ~(1 << LED);
			_delay_ms(100);

			Temperature = getTemperature();
			lcd_home();
			lcd_puts(double_to_string(Temperature));

			/* Automatically goes to TX mode */
			nrf24_send(double_to_string(Temperature));

			/* Wait for transmission to end */
			while(nrf24_isSending());
			_delay_ms(100);

			FLAG = 0;
			// Put CPU to sleep
			CPU_sleep();
		}
	}
}

ISR(TIMER1_OVF_vect){
	counter++;
	if (counter > 4){ // fires about every 10 seconds
		FLAG = 1;
		counter = 0;
	}
}
