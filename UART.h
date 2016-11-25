/*
 * UART.h
 *
 *  Created on: 1 de set de 2016
 *      Author: mathias
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Queue.h"
#include "GPIO_Pin.h"

#define FOSC 16000000

class UART {
public:
	enum BAUDRATE {
		B1200 = 1200, B2400 = 2400, B4800 = 4800,
		B9600 = 9600, B19200 = 19200, B38400 = 38400,
		B57600 = 57600, B115200 = 115200
	};
	enum DATASIZE {
		BITS5 = 0, BITS6, BITS7, BITS8, BITS9 = 3
	};
	enum PARITY {
		DISABLE = 0, EVEN = 2, ODD
	};
	enum STOPBITS {
		STOPB1 = 0, STOPB2
	};
	UART(BAUDRATE bd, DATASIZE ds, PARITY pt, STOPBITS sb);
	void put(char character);
	char get();
	void print(char *s);
	void println(char *s);
	void enable();
	void disable();
	static void isr_rx_handle(){
		rx.push(UDR0);
	};
	static void isr_tx_handle(){

		if(tx.length() > 0){
			UDR0 = tx.pop();
		}else{
			disable_tx();
		}

	}
private:
	typedef Queue<32> UART_Queue;
	static UART_Queue tx;
	static UART_Queue rx;
	BAUDRATE baud;
	DATASIZE data_size;
	PARITY parity;
	STOPBITS stopbits;
	static void disable_tx(){
		UCSR0B &= ~(1<<5);
	}
	static void enable_tx(){
		UCSR0B |= (1<<5);
	}
};

#endif /* UART_H_ */
