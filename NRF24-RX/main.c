/*
 * main.c
 *
 *  Created on: Jan 6, 2015
 *      Author: mikedanylov
 */

#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "nrf24.h"
#include "hd44780.h"

char buffer[8];
//uint8_t tx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};
uint8_t rx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};

int main(){

	/* init hardware pins */
	nrf24_init();
	lcd_init();
	/* Channel #2 , payload length: 4 */
	nrf24_config(2,8);
	/* Set the device addresses */
	//nrf24_tx_address(tx_address);
	nrf24_rx_address(rx_address);

	lcd_home();
	lcd_puts("Starting...");
	_delay_ms(1000);
	lcd_clrscr();

	while(1){
		if(nrf24_dataReady()){
			nrf24_getData(buffer);
			lcd_clrscr();
			lcd_home();
			lcd_puts(buffer);
			_delay_ms(10);
		}
	}
}
