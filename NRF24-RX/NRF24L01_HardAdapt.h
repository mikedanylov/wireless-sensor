/*
 * NRF24L01_HardAdapt.h
 *
 *  Created on: Jun 2, 2015
 *      Author: mdanylov
 */

#ifndef NRF24L01_HARDADAPT_H_
#define NRF24L01_HARDADAPT_H_

#include "NRF24L01/nrf24.h"
#include "Record.h"
#include <stdlib.h>
#include <string.h>
#include <avr/delay.h>

void transceiver_init();
void transceiver_send(Record* record);
Record transceiver_receive();
void transceiver_tx_address(uint8_t* addr);
void transceiver_rx_address(uint8_t* addr);
void transceiver_config();
void transceiver_set_channel(uint8_t channel);
void transceiver_set_payload(uint8_t payload);

#endif /* NRF24L01_HARDADAPT_H_ */
