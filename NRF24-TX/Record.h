/*
 * Record.h
 *
 *  Created on: Jun 2, 2015
 *      Author: mdanylov
 */

#ifndef RECORD_H_
#define RECORD_H_

/*
 * struct Record represents a packet sent by sensor node.
 * Since more than one sensor is going to be used, we need
 * more sophisticated way of communication between bunch of sensors
 * and single receiver. it should be aware from which sensor
 * the data is received in order to handle that data properly furthermore
 */

#include <stdio.h>

typedef struct{
	uint8_t sensor_id;
	uint8_t* sensor_data;
}Record;

void record_set_sensor_id(Record* record, uint8_t id);
void record_set_sensor_data(Record* record, uint8_t* data);

uint8_t record_get_sensor_id(Record* record);
uint8_t* record_get_sensor_data(Record* record);

#endif /* RECORD_H_ */
