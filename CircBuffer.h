/*
 * CircBuffer.h
 *
 *  Created on: 21 de set de 2016
 *      Author: mathias
 */

#ifndef CIRCBUFFER_H_
#define CIRCBUFFER_H_

#include <string.h>

template<unsigned int SIZE>
class CircBuffer {
public:
	CircBuffer() {
		memset(buffer, 0, SIZE*sizeof(unsigned int));
		this->pos = SIZE-1;
	}
	void update(unsigned int value){
		this->pos = ((this->pos == SIZE)? 0 : (this->pos+1));
		this->buffer[this->pos] = value;
	}
	unsigned int get(int pos){
		int aux;
		aux = (this->pos - pos) % SIZE;
		return this->buffer[aux];
	}
private:
	int pos;
	unsigned int buffer[SIZE];
};

#endif /* CIRCBUFFER_H_ */
