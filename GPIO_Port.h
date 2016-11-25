/*
 * GPIOPort.h
 *
 *  Created on: 31 de ago de 2016
 *      Author: arliones.hoeller
 */

#ifndef GPIO_PORT_H_
#define GPIO_PORT_H_

#include <avr/io.h>

namespace GPIO_PORT {

class GPIO_Port {
public:
    void dir(int p, int io);
    void set(int p, int val = 1);
    void clear(int p);
    int get(int p);

private:
    unsigned char pin;
    unsigned char ddr;
    unsigned char port;
};

extern GPIO_Port * portB;
extern GPIO_Port * portC;
extern GPIO_Port * portD;

} /* namespace GPIO_PORT */

#endif /* GPIO_PORT_H_ */
