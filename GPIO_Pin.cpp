#include <stdio.h>
#include <avr/io.h>

#include "GPIO_Pin.h"

GPIO_Pin::GPIO_Pin(int p, PinDirection io)
 : pin(p)
{
	if(pin < 8) {
		port = GPIO_PORT::portD;
	}
	else if(pin > 13) {
		port = GPIO_PORT::portC;
		pin -= 14;
	}
	else {
		port = GPIO_PORT::portB;
		pin -= 8;
	}

	port->dir(pin, io);
}

void GPIO_Pin::set(int val)
{
  port->set(pin, val);
}

int GPIO_Pin::get()
{
  return port->get(pin);
}
