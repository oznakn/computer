#ifndef TimeController_h
#define TimeController_h

#include <Timer.h>
#include <Time.h>
#include <DS3232RTC.h>

#include "LinkedList.h"
#include "CallbackController.h"
#include "Alarm.h"

void waitForSerial() {
  while (!Serial.available()) {

  }
}

int compareAlarms(Alarm** pAlarm1, Alarm** pAlarm2) {
  uint32_t value1, value2;
  Alarm* alarm1 = (*pAlarm1);
  Alarm* alarm2 = (*pAlarm2);

  value1 = (alarm1->getHour() * 60) + alarm1->getMinute();
  value2 = (alarm2->getHour() * 60) + alarm2->getMinute();

  return value1 > value2 ? 1 : -1;
}

class TimeController {
  private:
    static LinkedList<CallbackController*>* perSecondCallbackControllerList;
    static LinkedList<CallbackController*>* perMinuteCallbackControllerList;
    static LinkedList<CallbackController*>* alarmRunListenerList;
    static LinkedList<Alarm*>* alarmList;
    static Timer* timer;

    static void perSecondTimerCallback();
    static void perMinuteTimerCallback();
    static void sortAlarmList();

  public:
    static void init();
    static void postInit();
    static void update();
    static CallbackController* createAndAddSecondListener(CallbackListener*);
    static CallbackController* createAndAddMinuteListener(CallbackListener*);
    static CallbackController* createAndAddAlarmRunListener(CallbackListener*);
    static void addAlarm(Alarm*);
    static Alarm* createAndAddAlarm(CallbackListener*, int, int, bool = true);
    static Alarm* getNextAlarm();
    static LinkedList<Alarm*>* getAlarmList();
    static int getAlarmCount();
    static void pulse(uint8_t, unsigned long, uint8_t);
    static void oscillate(uint8_t, unsigned long, uint8_t);
    static void after(unsigned long, CallbackListener*);
    static void fetchTime();
    static String getFullTimeText(bool = false);
    static String getTimeText();
    static String getDateText(bool = false);
    static uint8_t getDayOfWeek();
};

Timer * TimeController::timer = new Timer();
LinkedList<CallbackController*> * TimeController::perSecondCallbackControllerList = new LinkedList<CallbackController*>;
LinkedList<CallbackController*> * TimeController::perMinuteCallbackControllerList = new LinkedList<CallbackController*>;
LinkedList<CallbackController*> * TimeController::alarmRunListenerList = new LinkedList<CallbackController*>;
LinkedList<Alarm*> * TimeController::alarmList = new LinkedList<Alarm*>;

void TimeController::init() {
  setSyncProvider(RTC.get);

  TimeController::timer->every(1000 , TimeController::perSecondTimerCallback);
  TimeController::timer->every(60000 , TimeController::perMinuteTimerCallback);
}

void TimeController::postInit() {
  TimeController::perSecondTimerCallback();
  TimeController::perMinuteTimerCallback();
}

void TimeController::update() {
  TimeController::timer->update();
}

void TimeController::pulse(uint8_t pin, unsigned long period, uint8_t startingValue) {
  TimeController::timer->pulse(pin, period, startingValue);
}

void TimeController::oscillate(uint8_t pin, unsigned long period, uint8_t startingValue) {
  TimeController::timer->oscillate(pin, period, startingValue);
}

void TimeController::after(unsigned long period, CallbackListener * callback) {
  TimeController::timer->after(period, callback);
}

void TimeController::perSecondTimerCallback() {
  for (int i = 0; i < TimeController::perSecondCallbackControllerList->size(); i++) {
    TimeController::perSecondCallbackControllerList->get(i)->runIfEnabled();
  }
}

void TimeController::perMinuteTimerCallback() {
  for (int i = 0; i < TimeController::perMinuteCallbackControllerList->size(); i++) {
    TimeController::perMinuteCallbackControllerList->get(i)->runIfEnabled();
  }

  int _hour = hour();
  int _minute = minute();

  for (int i = TimeController::alarmList->size() - 1; i >= 0; i--) {
    Alarm * alarm = TimeController::alarmList->get(i);

    if(alarm->runIfNeccesary(_hour, _minute)) {
      TimeController::alarmList->remove(i);

      delete alarm;
    }
  }

  for (int i = 0; i < TimeController::alarmRunListenerList->size(); i++) {
    TimeController::alarmRunListenerList->get(i)->runIfEnabled();
  }
}

CallbackController* TimeController::createAndAddSecondListener(CallbackListener * callback) {
  CallbackController * listener = new CallbackController(callback);
  listener->disable();

  TimeController::perSecondCallbackControllerList->add(listener);

  return listener;
}

CallbackController* TimeController::createAndAddMinuteListener(CallbackListener * callback) {
  CallbackController * listener = new CallbackController(callback);
  listener->disable();

  TimeController::perMinuteCallbackControllerList->add(listener);

  return listener;
}

CallbackController* TimeController::createAndAddAlarmRunListener(CallbackListener * callback) {
  CallbackController * listener = new CallbackController(callback);
  listener->disable();

  TimeController::alarmRunListenerList->add(listener);

  return listener;
}

void TimeController::addAlarm(Alarm* alarm) {
  TimeController::alarmList->add(alarm);
  TimeController::sortAlarmList();
}

Alarm* TimeController::createAndAddAlarm(CallbackListener* callbackListener, int hour, int minute, bool oneTime) {
  Alarm * alarm = new Alarm(callbackListener, hour, minute, oneTime);

  TimeController::addAlarm(alarm);

  return alarm;
}

Alarm* TimeController::getNextAlarm() {
  int _hour = hour();
  int _minute = minute();

  if (TimeController::alarmList->size() > 0) {
    for (int i = 0; i < TimeController::alarmList->size(); i++) {
      Alarm* alarm = TimeController::alarmList->get(i);

      if (alarm->getHour() >= _hour && alarm->getMinute() >= _minute) {
        return alarm;
      }
    }

    return TimeController::alarmList->get(0);
  }

  return NULL;
}

LinkedList<Alarm*>* TimeController::getAlarmList() {
  return TimeController::alarmList;
}

void TimeController::sortAlarmList() {
  TimeController::alarmList->sort(compareAlarms);
}

int TimeController::getAlarmCount() {
  return TimeController::alarmList->size();
}

void TimeController::fetchTime() {
  Serial.println("Enter Year");
  waitForSerial();
  int year = Serial.readString().toInt();

  Serial.println("Enter Month");
  waitForSerial();
  int month = Serial.readString().toInt();

  Serial.println("Enter Day");
  waitForSerial();
  int day = Serial.readString().toInt();

  Serial.println("Enter Hour");
  waitForSerial();
  int hour = Serial.readString().toInt();

  Serial.println("Enter Minute");
  waitForSerial();
  int minute = Serial.readString().toInt();

  setTime(hour , minute , 0 , day , month , year);
  RTC.set(now());

  TimeController::perSecondTimerCallback();
  TimeController::perMinuteTimerCallback();
}

String TimeController::getFullTimeText(bool cropYear) {
  return TimeController::getDateText(cropYear) + " " + TimeController::getTimeText();
}

String TimeController::getTimeText() {
  return timePropToText(hour()) + ":" + timePropToText(minute()) + ":" + timePropToText(second());
}

String TimeController::getDateText(bool cropYear) {
  String text = timePropToText(day()) + "." + timePropToText(month()) + ".";

  if (cropYear) text += String(year()).substring(2, 4);
  else text += year();

  return text;
}

// from 0 to 6, Sunday to Saturday
uint8_t TimeController::getDayOfWeek() {
  return ((now() / 86400) + 4) % 7;
}

#endif