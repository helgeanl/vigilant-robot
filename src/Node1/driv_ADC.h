/*
 * driv_ADC.h
 *
 * Created: 10.09.2015 13:33:28
 *  Author: helgeanl
 */ 


#ifndef DRIV_ADC_H_
#define DRIV_ADC_H_

/**
 Read value of ADC channel
 @param channel, ch1: joy Y, ch2: joy X, ch4: left slider, ch3: right slider
 @return value, 0-5V = 0-255
 */
uint8_t adc_read(char channel);

/**
 Initialize ADC
 */
void adc_init(void);


#endif /* DRIV_ADC_H_ */