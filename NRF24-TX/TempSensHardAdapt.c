/*
 * TempSensHardAdapt.c
 *
 *  Created on: May 31, 2015
 *      Author: mdanylov
 */

#include "TempSensHardAdapt.h"
#include <stdio.h>

uint8_t* sensor_get_temperature(){

	int8_t buff[7] = "";
	int8_t int_part = 0;
	int8_t two_decimal_part = 0;
	double temp_double = 0;

	temp_double = ds18b20_gettemp();
	int_part = temp_double;
	two_decimal_part = (temp_double - int_part) * 100;
	if (two_decimal_part < 0)
		two_decimal_part *= -1;
	sprintf(buff, "%02d.%02d C", int_part, two_decimal_part);

	return buff;
}
