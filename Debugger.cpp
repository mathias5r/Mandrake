/*
 * Debugger.cpp
 *
 *  Created on: 1 de set de 2016
 *      Author: mathias
 */

#include "Debugger.h"

Debugger::Debugger(bool state){
	UART uart(UART::B9600, UART::BITS8, UART::DISABLE, UART::STOPB1);
	this->ut = &uart;
	this->state = state;
}

void Debugger::debug(char *msg){
	if(state){
		this->ut->print(msg);
	}
}

void Debugger::debug(unsigned int value){
	char msg[10];
	sprintf((char*)msg,"%d",value);
	debug(msg);
}

void Debugger::debug(unsigned long value){
	char msg[10];
	sprintf((char*)msg,"%lu",value);
	debug(msg);
}

void Debugger::on_off(bool option){
	this->state = option;
}


