/*
 * Record.c
 *
 *  Created on: Jun 2, 2015
 *      Author: mdanylov
 */

#include "Record.h"

void record_set_sensor_id(Record* record, uint8_t id){
	record->sensor_id = id;
}
void record_set_sensor_data(Record* record, uint8_t* data){
	record->sensor_data = data;
}
uint8_t record_get_sensor_id(Record* record){
	return record->sensor_id;
}
uint8_t* record_get_sensor_data(Record* record){
	return record->sensor_data;
}
