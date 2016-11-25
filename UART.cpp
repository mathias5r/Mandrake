/*
 * UART.cpp
 *
 *  Created on: 1 de set de 2016
 *      Author: mathias
 */

#include "UART.h"

UART::UART_Queue UART::rx;
UART::UART_Queue UART::tx;

ISR(USART_RX_vect){
	UART::isr_rx_handle();
}

ISR(USART_UDRE_vect){
	UART::isr_tx_handle();
}

UART::UART(BAUDRATE bd, DATASIZE ds, PARITY pt, STOPBITS sb) {

	this->baud = bd;
	this->data_size = ds;
	this->parity = pt;
	this->stopbits = sb;

	unsigned int baud_rate = ((FOSC)/(this->baud*16UL)-1);

	//Baud rate
	UBRR0H = (baud_rate >> 8);
	UBRR0L = baud_rate;

	enable();

	//Data size
	if(this->data_size == BITS9){
		UCSR0B |= (1 << 2);
		UCSR0C |= (this->data_size << 1);
	}else{
		UCSR0C |= (this->data_size << 1);
	}

	//Parity
	UCSR0C |= (this->parity << 4);

	//Stop_bits
	UCSR0C |= (this->stopbits << 3);
}

void UART::put(char character){

	//The UDRE Flag indicates if the transmit
	//buffer (UDR) is ready to receive new data.
	//The UDR is ready when all the data is shifted out.

	this->tx.push(character);
	enable_tx();

}

char UART::get(){
	if(this->rx.length() > 0){
		return this->rx.pop();
	}
	return 0;
}

void UART::print(char * s){

	while(*s){
		put(*s);
		s++;
	}
}

void UART::println(char * s){
	print(s);
	put('\n');
}

void UART::enable(){
	UCSR0B |= (1<<4);
	UCSR0B |= (1<<3);
	UCSR0B |= (1<<7);
	UCSR0B |= (1<<5);
}

void UART::disable(){
	UCSR0B &= ~(1<<4);
	UCSR0B &= ~(1<<3);
	UCSR0B &= ~(1<<7);
	UCSR0B &= ~(1<<5);
}







