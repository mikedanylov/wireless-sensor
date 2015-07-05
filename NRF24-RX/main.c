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
#include "NRF24L01/nrf24.h"
#include "HD44780/hd44780.h"
#include "NRF24L01_HardAdapt.h"
#include "Record.h"

int main(){

	Record records[4];
	uint8_t rx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
	lcd_init();
	transceiver_init();
	transceiver_set_channel(2);
	transceiver_set_payload(8);
	transceiver_config();
	transceiver_rx_address(rx_address);

	lcd_home();
	lcd_puts("Starting...");
	_delay_ms(1000);
	lcd_clrscr();

	while(1){
		records[0] = transceiver_receive();
		/*
		 * TODO
		 * forward data directly to UART
		 */
		lcd_home();
		lcd_puts(records[0].sensor_data);
		_delay_ms(1000);
		lcd_clrscr();
	}
}
