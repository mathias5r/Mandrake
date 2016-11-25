/*
 * ADCconv.cpp
 *
 *  Created on: 13 de set de 2016
 *      Author: mathias
 */

#include "ADCconv.h"
#include "Debugger.h"

ADCconv::ADC_Buffer* ADCconv::buffers[];

ISR(ADC_vect){
	ADCconv::isr_handle();
}

ADCconv::ADCconv(ADC_CHANNEL ch, ADC_PRESCALLER pr, VOLTAGE_REFERENCE vt){

	buffers[ch] = &this->buffer;
	this->channel = ch;
	this->prescaller = pr;
	this->volt = vt;

	config(this->channel,this->prescaller,this->volt);

	enable();

	start_conversion();

}

unsigned int ADCconv::voltage(){


	unsigned int value = read();

	value = (value >> 4);

	unsigned long aux = ((unsigned long)value*5000);

	value = aux >> 10;

	return value;

}

unsigned int ADCconv::get_channel(){

	return this->channel;

}

void ADCconv::start_conversion(){

	/*Set a rigth-ajust. A right-justified result means that bits [(N-1):0]
	 * (where N is the number of bits of precision) of the register contain
	 *  the ADC value and the most-significant bits of the register are set
	 *   to zero.*/
	ADMUX &= ~(1 << ADLAR);

	/*Enable the auto-triggering*/
	ADCSRA |= (1 << ADATE);

	/*Set trigger mode to free running. This means that as soon as an ADC has
	 *finished, the next will be immediately started.*/
	ADCSRB &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));

	/*Enable the ADC interrupt. Without this, the internal interrupt will not
	 * trigger.*/
	ADCSRA |= (1 << ADIE);

	/*Enable the global interrupts*/
	sei();

	/*Start the ADC conversion*/
	ADCSRA |= (1 << ADSC);

}

void ADCconv::config(ADC_CHANNEL ch, ADC_PRESCALLER pr, VOLTAGE_REFERENCE vt){

	/*Set the voltage reference for the ADC as AVcc with external capacitor
	 * at AREF pin*/
	ADMUX |= (vt << 6);//(1<<REFS0);

	/*Clear MUX3..0 in preparation for setting the analog input*/
	ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));

	/*Selection of the channel*/
	ADMUX |= ch;

	/*Set prescaller to 128 (16000KHz/128 = 125KHz)
	 *Above 200KHz 10-bit results are not reliable.*/
	ADCSRA |= pr;//((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0));

}

void ADCconv::enable(){

	/*Enable the ADC*/
	ADCSRA |= (1 << ADEN);
}

void ADCconv::disable(){

	/*Disable the ADC*/
	ADCSRA &= ~(1 << ADEN);

}

unsigned int ADCconv::read(){

    unsigned int value = 0;

	ATOMIC_BLOCK(ATOMIC_FORCEON){
    	this->atomic_buffer = this->buffer;
    }

	for (int i = 0; i < 16; i++){
		value += this->atomic_buffer.get(i);
	}

	return value;

}






