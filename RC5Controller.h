/* 
* RC5Controller.h
*
* Created: 2019. 01. 01. 22:54:50
* Author: Huszty Gergo
*/


#ifndef __RC5CONTROLLER_H__
#define __RC5CONTROLLER_H__

#include "RC5.h"

class RC5CommandHandler {
public:
  virtual void buttonPressed() = 0;
};

template<uint8_t T_SIZE> class RC5Controller: public RC5Handler {
  RC5Controller( const RC5Controller &c );
	RC5Controller& operator=( const RC5Controller &c );
  RC5CommandHandler *handlers[T_SIZE];
  uint16_t commands[T_SIZE];
public:
	RC5Controller() {};
	~RC5Controller() {};
  void commandReceived(uint16_t message) {
    message &= ~(TOGGLE_MASK);
    uint8_t i = 0;
    do {
      if(message == commands[i] && handlers[i]) {
        handlers[i]->buttonPressed();
      }
    } while(++i < T_SIZE);
  }
  void setHandler(uint8_t index, RC5CommandHandler *handler) {
    handlers[index] = handler;
  }
  void setCommand(uint8_t index, uint16_t command) {
    commands[index] = command;
  }
};

#endif //__RC5CONTROLLER_H__
