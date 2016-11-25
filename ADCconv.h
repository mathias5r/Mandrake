/*
 * ADCconv.h
 *
 *  Created on: 13 de set de 2016
 *      Author: mathias
 */

#ifndef ADCCONV_H_
#define ADCCONV_H_

#include "GPIO_Pin.h"
#include "CircBuffer.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

class ADCconv {
public:
	enum ADC_CHANNEL {
		CH0 = 0,CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8
	};
	enum ADC_PRESCALLER{
		FACTOR2 = 1, FACTOR4, FACTOR8, FACTOR16, FACTOR32, FACTOR64, FACTOR128
	};
	enum VOLTAGE_REFERENCE{
		AREF = 0, AVCC, INTELNAL=3
	};
	ADCconv(ADC_CHANNEL ch, ADC_PRESCALLER pr, VOLTAGE_REFERENCE vt);
	unsigned int voltage();
	unsigned int get_channel();
	void enable();
	void disable();
	static void isr_handle(){
		int ch = ADMUX & 0x0f;
		buffers[ch]->update(ADCL | (ADCH << 8));
	}

private:
	ADC_CHANNEL channel;
	ADC_PRESCALLER prescaller;
	VOLTAGE_REFERENCE volt;
	static const int channels = 9;
	typedef CircBuffer<16> ADC_Buffer;
	ADC_Buffer buffer;
	ADC_Buffer atomic_buffer;
	static ADC_Buffer * buffers[channels];
	void start_conversion();
	void config(ADC_CHANNEL ch, ADC_PRESCALLER pr, VOLTAGE_REFERENCE vt);
	unsigned int read();
};

#endif /* ADCCONV_H_ */
