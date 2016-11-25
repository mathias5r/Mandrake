#ifndef __GPIO_Pin__
#define __GPIO_Pin__

#include "GPIO_Port.h"

class GPIO_Pin {
private:

  int pin;
  GPIO_PORT::GPIO_Port * port;

public:

  enum PinDirection {
      INPUT  = 0,
      OUTPUT = 1
  };

  GPIO_Pin(int p, PinDirection io); //io => true: output; false: input.
  void on() { set(1); }
  void off() { set(0); }
  void set(int val = 1);
  int get();
};

#endif // __GPIO_Pin__
