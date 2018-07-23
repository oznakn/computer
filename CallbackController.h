#ifndef CallbackController_h
#define CallbackController_h

#include "CallbackListener.h"
#include "LinkedList.h"

class CallbackController {
  private:
    static int idCounter;
    static int idCreator();

    int mIsEnabled = true;
    String mData = "";
    CallbackListener* mCallbackListener;

  public:
    int mIndex;

    CallbackController(CallbackListener*);
    CallbackController(CallbackListener*, String);
    void enable();
    void disable();
    CallbackListener* getCallbackListener();
    void setData(String);
    String getData();
    void removeFromList(LinkedList<CallbackController*>*);
    boolean isEnabled();
    void run();
    void runIfEnabledAndData(String);
    void runIfEnabled();
};

int CallbackController::idCounter = 0;

int CallbackController::idCreator() {
  return ++CallbackController::idCounter;
}

CallbackController::CallbackController(CallbackListener* callback) {
  this->mCallbackListener = callback;

  this->mIndex = CallbackController::idCreator();
}

CallbackController::CallbackController(CallbackListener* callback, String data) {
  this->mCallbackListener = callback;
  this->mData = data;

  this->mIndex = CallbackController::idCreator();
}

void CallbackController::enable() {
  this->mIsEnabled = true;
}

void CallbackController::disable() {
  this->mIsEnabled = false;
}

void CallbackController::setData(String data) {
  this->mData = data;
}

String CallbackController::getData() {
  return this->mData;
}

bool CallbackController::isEnabled() {
  return this->mIsEnabled;
}

CallbackListener* CallbackController::getCallbackListener() {
  return this->mCallbackListener;
}

void CallbackController::removeFromList(LinkedList<CallbackController*>* list) {
  for (int i = 0; i < list->size(); i++) {
    if (list->get(i)->mIndex == this->mIndex) {
      list->remove(i);
      break;
    }
  }
}

void CallbackController::run() {
  (*this->mCallbackListener)();
}

void CallbackController::runIfEnabled() {
  if (this->isEnabled()) {
    this->run();
  }
}

void CallbackController::runIfEnabledAndData(String data) {
  if (this->isEnabled() && this->mData.equals(data)) {
    this->run();
  }
}

#endif
