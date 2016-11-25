#include "GPIO_Pin.h"
#include "UART.h"
#include "Debugger.h"
#include "ADCconv.h"
#include <util/delay.h>
#include <stdlib.h>

GPIO_Pin led(13,GPIO_Pin::OUTPUT);
Debugger d(true);
ADCconv adc(ADCconv::CH0, ADCconv::FACTOR128, ADCconv::AVCC);

int main(){
	d.debug("reset\n");

	while(1){

		unsigned int pot_value =  adc.voltage();

		if(pot_value >= 3000){
			led.set(1);
			d.debug("Voltage:");
			d.debug(pot_value);
			d.debug(" mV - Led On! \n");
			_delay_ms(1000);
		}else{
			led.set(0);
			d.debug("Voltage: ");
			d.debug(pot_value);
			d.debug(" mV - Led Off! \n");
			_delay_ms(1000);
		}
	}

	return 0;
}
