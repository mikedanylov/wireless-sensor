/*
 * ADC.h
 *
 *  Created on: Dec 14, 2014
 *      Author: mikedanylov
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdio.h>
#include <avr/io.h>

#define ADC_PIN 0 		// ADC channel 0 PORTC0, pin 23 on 328p
#define VREF 	3300.0 	// reference voltage of ADC
#define VZERO 	500.0	// voltage which sensors outputs when temperature is 0
#define VSTEP 	10.0	// sensor step = 1 degree Celcius
#define ADCRES 	1024.0 	// ADC resolution 10 bit
#define calibr 	1.1 	// Use calibration for sensor if needed

void 		InitADC();
uint16_t 	ReadADC(uint8_t ADCchannel);
double		getTemperature();
char* 		double_to_string(double number);

#endif /* ADC_H_ */
