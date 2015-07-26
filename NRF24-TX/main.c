/*
 * main.c
 *
 *  Created on: Jan 6, 2015
 *      Author: mikedanylov
 */

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/sleep.h>
#include <avr/power.h>

#include "uart/uart.h"
#include "adc/adc.h"
#include "timer2/timer2.h"
#include "Record.h"
#include "NRF24L01/nrf24.h"

#define led_tx PD6
#define power_on PB2
#define UART_BAUD_RATE 300
#define WAIT_TIME 10
#define NRF24_CH 2
#define PAYLOAD 8

uint8_t TIMER_OVERFLOW = 10;

ISR(TIMER2_OVF_vect);

int main(){

	double temperature;
	uint16_t adc_temp_value;
	char uart_buff[50];
	char nrf24_buff[PAYLOAD];
	uint8_t tx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
	Record record;

	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
	adc_init();
	sei(); // needed after uart_init
	timer2_init();
	record_set_sensor_id(&record, 1); // id should be unique for each sensor

	DDRD = DDRD | (1<<led_tx);// Make LED pin of PORTD an output
	PORTD &= ~(1 << led_tx);// Set led_tx low

	DDRB = DDRB | (1<<power_on);// Make Transistor pin of PORTB an output
	PORTB |= 1 << power_on;// set pin low

	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	power_all_disable();
	power_timer2_enable();
	power_usart0_enable();

	uart_puts("\r\nInitialization completed!\r\n\r\n");
	_delay_ms(1000);

	while(1){
		if (TIMER_OVERFLOW >= WAIT_TIME){

			timer2_cli();
			TIMER_OVERFLOW = 0; // reset interrupt counter

			// enable modules required for operation
			power_adc_enable();
			power_spi_enable();
			power_usart0_enable();
//			power_all_enable();

			PORTD |= 1 << led_tx;// Set led_tx high indicating that transmission has started
			PORTB |= 1 << power_on;// Set Transistor pin high, supplying power to transceiver and sensor

			// setup nrf24 chip
			nrf24_init();
			nrf24_config(NRF24_CH, PAYLOAD);
			nrf24_rx_address(tx_address);

//			// 1. Get data from sensor
			adc_temp_value = adc_read_oversampled(PC0);
			// debugging
			sprintf(uart_buff, "ADC value: 	%d", adc_temp_value);
			uart_puts(uart_buff);
			uart_puts("\r\n");
			_delay_ms(500);

			// 2. Convert ADC value to temperature
			temperature = adc_toint(adc_temp_value);
			adc_dtos(temperature, nrf24_buff);
			// debugging
			uart_puts("Temperature: 	");
			uart_puts(nrf24_buff);
			uart_puts(" C\r\n");
			_delay_ms(800);

			// 3. encapsulate temperature to Record type
//			record_set_sensor_data(&record, uart_buff);

			// 4. Transmit data
			nrf24_send(nrf24_buff);

			// 5. Poweroff sensor
			PORTD &= ~(1 << led_tx);// Set led_tx low indicating that transmission has been completed
			PORTB &= ~(1 << power_on); // Set  pin low cutting power off.

			// 6. return used modules to disabled state
			power_adc_disable();
			power_spi_disable();
			power_usart0_disable();
			timer2_sei();

			nrf24_powerDown();
		}
		// Put CPU to sleep mode
		cli();
		sleep_enable();
		sei();
		sleep_cpu();
		sleep_disable();
	}
}

ISR(TIMER2_OVF_vect){
	TIMER_OVERFLOW++;
}
