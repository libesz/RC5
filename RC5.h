/*
 *  RC5 Arduino Library
 *  Guy Carpenter, Clearwater Software - 2013
 *
 *  Licensed under the BSD2 license, see LICENSE for details.
 *
 *  All text above must be included in any redistribution.
 */

#ifndef RC5_h
#define RC5_h

/* This include shall deliver the missing compiler and standard lib functions,
 * which are not available in case of avr-g++ compilation.
 * See: https://www.avrfreaks.net/comment/341297#comment-341297
 */
#include "CppStubs.h"
#include <stdint.h>

#define TOGGLE_MASK   0x0800  // 1 bit
#define TOGGLE_SHIFT  11
#define ADDRESS_MASK  0x7C0  //  5 bits
#define ADDRESS_SHIFT 6
#define COMMAND_MASK  0x003F //  low 6 bits
#define COMMAND_SHIFT 0

class RC5Handler {
public:
  virtual void commandReceived(uint16_t message) = 0;
};

class RC5 {
    uint8_t pin;
    uint8_t state;
    uint16_t time0;
    uint32_t lastValue;
    uint16_t bits;
    uint16_t command;
    RC5Handler *handler;
 public:
    RC5(RC5Handler *newHandler);
    void reset();
    bool read(uint16_t *message);
    bool read(uint8_t *toggle, uint8_t *address, uint8_t *command);
    void decodeEvent(uint8_t event);
    void decodePulse(uint8_t signal, uint32_t period);
    void inputChanged(uint8_t value);
};

#endif // RC5_h
