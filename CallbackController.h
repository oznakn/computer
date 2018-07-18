#ifndef CallbackController_h
#define CallbackController_h

#include "CallbackListener.h"

class CallbackController {
  private:
    int mIsEnabled = true;
    String mData = "";
    CallbackListener * mCallbackListener;

    void init();

  public:
    CallbackController(CallbackListener *);
    CallbackController(CallbackListener *, String);
    void enable();
    void disable();
    boolean isEnabled();
    CallbackListener* getCallbackListener();
    void run();
    void runIfEnabledAndData(String);
    void runIfEnabled();
    String getData();
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

bool CallbackController::isEnabled() {
  return this->mIsEnabled;
}

CallbackListener* CallbackController::getCallbackListener() {
  return this->mCallbackListener;
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

String CallbackController::getData() {
  return this->mData;
}

#endif
