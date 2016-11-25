/*
 * Debugger.h
 *
 *  Created on: 1 de set de 2016
 *      Author: mathias
 */

#include "UART.h"
#include <string.h>
#include <stdio.h>

#ifndef DEBUGGER_H_
#define DEBUGGER_H_

class Debugger {
public:
	Debugger(bool state = false);
	void debug(char *msg);
	void debug(unsigned int value);
	void debug(unsigned long value);
	void on_off(bool option);
private:
	UART* ut;
	bool state;
};

#endif /* DEBUGGER_H_ */
