/*
 * main.c
 *
 *  Created on: Jan 6, 2015
 *      Author: mikedanylov
 */

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "NRF24L01/nrf24.h"
#include "HD44780/hd44780.h"

#define PAYLOAD 8
#define NRF_CH 2

int main(){

	char nrf_buff[PAYLOAD];
	uint8_t rx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};

	nrf24_init();
	lcd_init();
	nrf24_config(NRF_CH, PAYLOAD);
	nrf24_rx_address(rx_address);

	lcd_home();
	lcd_puts("Starting...");
	_delay_ms(1000);
	lcd_clrscr();

	while(1){
		if(nrf24_dataReady()){
			nrf24_getData(nrf_buff);
			lcd_clrscr();
			lcd_home();
			lcd_puts(nrf_buff);
			lcd_puts("       ");
			_delay_ms(10);
		}
	}
}
