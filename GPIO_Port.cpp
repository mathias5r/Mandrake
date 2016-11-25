/*
 * GPIOPort.cpp
 *
 *  Created on: 31 de ago de 2016
 *      Author: arliones.hoeller
 */

#include "GPIO_Port.h"

namespace GPIO_PORT {

enum PORT_ADDR_BASE {
    AVR_PORTB = 0x0023,
    AVR_PORTC = 0x0026,
    AVR_PORTD = 0x0029
};

GPIO_Port * portB = reinterpret_cast<GPIO_Port*>(AVR_PORTB);
GPIO_Port * portC = reinterpret_cast<GPIO_Port*>(AVR_PORTC);
GPIO_Port * portD = reinterpret_cast<GPIO_Port*>(AVR_PORTD);

void GPIO_Port::dir(int p, int io) {
    if (io)
        ddr |= (1 << p);
    else
        ddr &= ~(1 << p);
}
void GPIO_Port::set(int p, int val) {
    if (val)
        port |= (1 << p);
    else
        port &= ~(1 << p);
}
void GPIO_Port::clear(int p) {
    set(p,0);
}
int GPIO_Port::get(int p) {
    return pin & (1 << p);
}



} /* namespace GPIO_PORT */
