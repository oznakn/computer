#ifndef Alarm_h
#define Alarm_h

#include "CallbackController.h"

String timePropToText(int value) {
  String text = String(value);

  if (value < 10) {
    text = "0" + text;
  }

  return text;
}

class Alarm {
  private:
    int mHour;
    int mMinute;
    bool mIsEnabled = true;
    bool mOneTime = true;
    CallbackListener* mCallbackListener;

  public:
    Alarm(CallbackListener*, int, int, bool = true);
    int getHour();
    int getMinute();
    void run();
    bool runIfNeccesary(int, int);
    String getAsText();
};

Alarm::Alarm(CallbackListener* callbackListener, int hour, int minute, bool oneTime) {
  this->mCallbackListener = callbackListener;
  this->mHour = hour;
  this->mMinute = minute;
  this->mOneTime = oneTime;
}

int Alarm::getHour() {
  return this->mHour;
}

int Alarm::getMinute() {
  return this->mMinute;
}

void Alarm::run() {
  (*this->mCallbackListener)();
}

bool Alarm::runIfNeccesary(int hour, int minute) {
  if (this->mIsEnabled && hour == this->mHour && minute == this->mMinute) {
    this->run();

    if (this->mOneTime) {
      this->mIsEnabled = false;

      return true;
    }
    else {
      this->run();
    }
  }

  return false;
}

String Alarm::getAsText() {
  return timePropToText(this->getHour()) + ":" + timePropToText(this->getMinute());
}

#endif