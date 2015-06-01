/*
 * TempSensHardAdapt.c
 *
 *  Created on: May 31, 2015
 *      Author: mdanylov
 */

#include "TempSensHardAdapt.h"
#include <stdio.h>

char* getTemperature(){

	char* buff = "";
	int int_part = 0;
	int two_decimal_part = 0;
	double temp_double = 0;

	temp_double = ds18b20_gettemp();
	int_part = temp_double;
	two_decimal_part = (temp_double - int_part) * 100;
	sprintf(buff, "%02d.%02d C", int_part, two_decimal_part);

	return buff;
}
