/*
 * main.c
 *
 *  Created on: Jan 6, 2015
 *      Author: mikedanylov
 */
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <math.h>
#include "ADC.h"
#include "nrf24.h"
#include "hd44780.h"

double volatile Temperature;
char buffer[PAYLOAD];
uint8_t tx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};

int main(){

	nrf24_init();
	InitADC();
	lcd_init();

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

		// reading + displaying temperature
		Temperature = getTemperature();
		lcd_home();
		lcd_puts(double_to_string(Temperature));

		/* Automatically goes to TX mode */
		nrf24_send(double_to_string(Temperature));

		/* Wait for transmission to end */
		while(nrf24_isSending());
		_delay_ms(100);
	}
}

