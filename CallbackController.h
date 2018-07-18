#ifndef CallbackController_h
#define CallbackController_h

#include "CallbackListener.h"
#include "LinkedList.h"

class CallbackController {
  private:
    int mIsEnabled = true;
    int mIndex = -1;
    String mData = "";
    CallbackListener * mCallbackListener;

    void init();

  public:
    CallbackController(CallbackListener *);
    CallbackController(CallbackListener *, String);
    void enable();
    void disable();
    CallbackListener* getCallbackListener();
    void setIndex(int);
    int getIndex();
    void setData(String);
    String getData();
    void removeFromList(LinkedList<CallbackController*>*);
    boolean isEnabled();
    void run();
    void runIfEnabledAndData(String);
    void runIfEnabled();
};

CallbackController::CallbackController(CallbackListener * callback) {
  this->mCallbackListener = callback;

  this->init();
}

CallbackController::CallbackController(CallbackListener * callback, String data) {
  this->mCallbackListener = callback;
  this->mData = data;

  this->init();
}

void CallbackController::init() {

}

void CallbackController::enable() {
  this->mIsEnabled = true;
}

void CallbackController::disable() {
  this->mIsEnabled = false;
}


void CallbackController::setIndex(int index) {
  this->mIndex = index;
}

int CallbackController::getIndex() {
  return this->mIndex;
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
  if (this->mIndex != -1) {
    list->remove(this->mIndex);
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
