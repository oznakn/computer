#ifndef Alarm_h
#define Alarm_h

#include "CallbackController.h"
#include "LinkedList.h"

typedef void (AlarmHandler) (int);

String _alarmTimePropToText(int value) {
  String text = String(value);

  if (value < 10) {
    text = "0" + text;
  }

  return text;
}

int _alarmId = 0;

int _alarmIdCreator() {
  return ++_alarmId;
}

class Alarm {
  private:
    int mHour;
    int mMinute;
    bool mIsEnabled = true;
    bool mOneTime = true;
    int mBuzzerMode = 0;

  public:
    static AlarmHandler* alarmHandler;

    static void setAlarmHandler(AlarmHandler*);

    int mIndex = _alarmIdCreator();

    Alarm(int, int, bool, int);
    int getHour();
    int getMinute();
    void run();
    bool runIfNeccesary(int, int);
    String getHourAsText();
    String getMinuteAsText();
    String getAsText();
    void increaseHour();
    void decreaseHour();
    void increaseMinute();
    void decreaseMinute();
    void setOneTime(bool);
    bool getOneTime();
    void setBuzzerMode(int);
    int getBuzzerMode();
    void removeFromList(LinkedList<Alarm*>*);
};

AlarmHandler* Alarm::alarmHandler = NULL;

void Alarm::setAlarmHandler(AlarmHandler* alarmHandler) {
  Alarm::alarmHandler = alarmHandler;
}

Alarm::Alarm(int hour, int minute, bool oneTime, int buzzerMode) {
  this->mHour = hour;
  this->mMinute = minute;
  this->mOneTime = oneTime;
  this->mBuzzerMode = buzzerMode;
}

int Alarm::getHour() {
  return this->mHour;
}

int Alarm::getMinute() {
  return this->mMinute;
}

void Alarm::run() {
  if (Alarm::alarmHandler != NULL) {
      (*Alarm::alarmHandler)(this->mBuzzerMode);
  }
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

String Alarm::getHourAsText() {
  return _alarmTimePropToText(this->getHour());
}

String Alarm::getMinuteAsText() {
  return _alarmTimePropToText(this->getMinute());
}

String Alarm::getAsText() {
  return this->getHourAsText() + ":" + this->getMinuteAsText();
}

void Alarm::increaseHour() {
  this->mHour++;

  if (this->mHour > 23) this->mHour = 0;
}

void Alarm::decreaseHour() {
  this->mHour--;

  if (this->mHour < 0) this->mHour = 23;
}

void Alarm::increaseMinute() {
  this->mMinute++;

  if (this->mMinute > 59) this->mMinute = 0;
}

void Alarm::decreaseMinute() {
  this->mMinute--;

  if (this->mMinute < 0) this->mMinute = 59;
}

void Alarm::setOneTime(bool oneTime) {
  this->mOneTime = oneTime;
}

bool Alarm::getOneTime() {
  return this->mOneTime;
}

void Alarm::setBuzzerMode(int buzzerMode) {
  this->mBuzzerMode = ((buzzerMode + 4) % 4); // 4 is total buzzer Mode count
}

int Alarm::getBuzzerMode() {
  return this->mBuzzerMode;
}

void Alarm::removeFromList(LinkedList<Alarm*>* list) {
  for (int i = 0; i < list->size(); i++) {
    if (list->get(i)->mIndex == this->mIndex) {
      list->remove(i);
      break;
    }
  }
}

#endif