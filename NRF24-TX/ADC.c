/*
 * ADC.c
 *
 *  Created on: Dec 14, 2014
 *      Author: mikedanylov
 */
#include "ADC.h"

/* AVR ADC must be clocked at frequency between 50 and 200kHz.
So we need to set proper prescaller bits so that scaled system clock would fit in this range.
As our AVR is clocked at 16MHz we are going to use 128 scaling factor
by setting ADPS0, ADPS1 and ADPS2 bits in ADCSRA register.
This gives 16000000/128=125kHz of ADC clock */
void 		InitADC(){
 // Select Vref=AVcc
 ADMUX |= (1<<REFS0);
 //set prescaller to 128 and enable ADC
 ADCSRA |= (1<<ADPS2);
 ADCSRA |= (1<<ADPS1);
 ADCSRA |= (1<<ADPS0);
 ADCSRA |= (1<<ADEN);
 //ADCSRA |= (1<<ADIE);
}

/* Before selecting ADC channel in ADMUX register we use a mask (0b00001111)
which protects from unintentional alteration of ADMUX register.
After channel is selected we start single conversion by setting ADSC bit in ADCSRA register.
This bit remains high until conversion is complete.
So we are going to use this bit as indicator to decide when data is ready.
So we return ADC value after ADSC bit is reset. */
uint16_t 	ReadADC(uint8_t ADCchannel){
 //select ADC channel with safety mask
 ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
 // put ADC to sleep mode
 MCUCR |= 1<<SM0;
 MCUCR |= 1<<SE;
 //single conversion mode
 ADCSRA |= (1<<ADSC);
 // wait until ADC conversion is complete
 while( ADCSRA & (1<<ADSC) );
 return ADC;
}

double 		getTemperature(){

	return ((ReadADC(ADC_PIN) - ADCRES * VZERO/VREF) * VREF/ADCRES/* * calibr*/) / VSTEP;

}

char* 		double_to_string(double number){
	int round;
	int reminder;
	char* buf_tmp;

	round = number;
	reminder = (number - round) * 100;
	if (reminder < 0) // display negative temperature properly
		reminder *= -1;
	sprintf(buf_tmp, "%02d.%02d C\0", round, reminder);
	return buf_tmp;
}
