/*
 * NRF24L01_HardAdapt.c
 *
 *  Created on: Jun 2, 2015
 *      Author: mdanylov
 */

#include "NRF24L01_HardAdapt.h"

void transceiver_init(){
	nrf24_init();
}
void transceiver_send(Record* record){

	uint8_t id;
	uint8_t* data;
	uint8_t* res_str;

	id = record_get_sensor_id(record);
	data = record_get_sensor_data(record);
	res_str = (uint8_t*)malloc(sizeof(id)+sizeof(data));

	strcpy(res_str, &id);
	strcat(res_str, data);

	nrf24_send(res_str);
	while(nrf24_isSending());// Wait for transmission to end
	_delay_ms(100);
	free(res_str);
}
Record transceiver_receive(){

	Record result;
	uint8_t* buffer;

	buffer = (uint8_t*)malloc(PAYLOAD);
	if(nrf24_dataReady())
		nrf24_getData(buffer);

	record_set_sensor_id(&result, buffer[0]);// first element of buffer is id
	record_set_sensor_data(&result, &buffer[1]);// start from second element

	free(buffer);
	return result;
}
void transceiver_tx_address(uint8_t* addr){
	nrf24_tx_address(addr);// Set the device addresses
}
void transceiver_rx_address(uint8_t* addr){
	nrf24_rx_address(addr);
}
void transceiver_config(){
	nrf24_config(NRF24_CH, PAYLOAD);// Channel, payload length
}
void transceiver_set_channel(uint8_t channel){
	nrf24_set_channel(channel);
}
void transceiver_set_payload(uint8_t payload){
	nrf24_set_payload(payload);
}
