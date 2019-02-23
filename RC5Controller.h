/* 
* RC5Controller.h
*
* Created: 2019. 01. 01. 22:54:50
* Author: Huszty Gergo
*/


#ifndef __RC5CONTROLLER_H__
#define __RC5CONTROLLER_H__

#include "RC5.h"

class RC5RateLimiter {
  public:
  virtual bool grant() = 0;
};

class RC5StorageHandler {
  public:
  virtual void save(const uint16_t commands[], uint8_t length) = 0;
  virtual void load(uint16_t commands[], uint8_t length) = 0;
};

class RC5CommandHandler {
  public:
  virtual void buttonPressed() const = 0;
};

class RC5LearningHook {
  public:
  virtual void startLearningOf(uint8_t index) = 0;
  virtual void doneLearningOf(uint8_t index, uint16_t command) = 0;
};

template<uint8_t T_SIZE> class RC5Controller: public RC5Handler {
  RC5Controller( const RC5Controller &c );
	RC5Controller& operator=( const RC5Controller &c );
  const RC5CommandHandler *handlers[T_SIZE];
  uint16_t commands[T_SIZE];
  RC5LearningHook *learningHook;
  RC5StorageHandler *storageHandler;
  RC5RateLimiter *limiter;
  int8_t learningIndex;
public:
	RC5Controller(RC5LearningHook *newLearningHook,
                RC5StorageHandler *newStorageHandler,
                RC5RateLimiter *newLimiter): learningHook(newLearningHook),
                                             storageHandler(newStorageHandler),
                                             limiter(newLimiter),
                                             learningIndex(-1) {
    storageHandler->load(commands, T_SIZE);
  };
	~RC5Controller() {};
  void commandReceived(uint16_t message) {
    message &= ~(TOGGLE_MASK);
    if(!limiter->grant()) {
      return;
    }
    if(learningIndex >=0) {
      learningHook->doneLearningOf(learningIndex, message);
      setCommand(learningIndex, message);
      if(++learningIndex < T_SIZE) {
        learningHook->startLearningOf(learningIndex);
      } else {
        storageHandler->save(commands, T_SIZE);
        learningIndex = -1;
      }
    } else {
      uint8_t i = 0;
      do {
        if(message == commands[i] && handlers[i]) {
          handlers[i]->buttonPressed();
        }
      } while(++i < T_SIZE);
    }    
  }
  void setHandler(uint8_t index, const RC5CommandHandler *handler) {
    handlers[index] = handler;
  }
  void setCommand(const uint8_t index, const uint16_t command) {
    commands[index] = command;
  }
  void startLearningAll() {
    learningIndex = 0;
    learningHook->startLearningOf(0);
  }
  bool isLearningOngoing() {
    return !(learningIndex==-1);
  }
};

#endif //__RC5CONTROLLER_H__
