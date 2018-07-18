#ifndef MainPage_h
#define MainPage_h

// #include "MemoryFree.h"

#include "TimeController.h"
#include "LCDController.h"
#include "LedAndBuzzerController.h"
#include "PushButtonController.h"
#include "TemperatureController.h"

#include "Page.h"


class MainPage : public Page {
  private:
    CallbackController* mSecondTimeChangedCallbackController;
    CallbackController* mMinuteTimeChangedCallbackController;
    CallbackController* mOnAlarmRunCallbackController;

  public:
    void init(PageChangeFunction*);
    void apply();
    void start();
    void stop();
    void onEnable();
    void onDisable();
    void onLock();
    void onUnlock();
};

MainPage* _mainPage;

void _mainPageOnSecondTimeChanged() {
  LCDController::writeTime(TimeController::getTimeText());
  // Serial.println(freeMemory());
}

void _mainPageOnMinutetimeChanged() {
  LCDController::writeDate(TimeController::getDateText(true), TimeController::getDayOfWeek());
  LCDController::writeTemperature(TemperatureController::getTemperature());
  LCDController::writeHumidity(TemperatureController::getHumidity());
}

void _mainPageOnAlarmRun() {
  LCDController::writeNextAlarm(TimeController::getNextAlarm());
}

void _mainPageOnButton1HIGH() {
  LedAndBuzzerController::setBuzzer(LedAndBuzzerController::BUZZER_ON);
}

void _mainPageOnButton1LOW() {
  LedAndBuzzerController::setBuzzer(LedAndBuzzerController::BUZZER_OFF);
}

void _mainPageOnButton2HIGH() {
  LedAndBuzzerController::setBlueLed(LedAndBuzzerController::LED_ON);
}

void _mainPageOnButton2LOW() {
  LedAndBuzzerController::setBlueLed(LedAndBuzzerController::LED_OFF);
}

void _mainPageOnButton3HIGH() {
  LedAndBuzzerController::setGreenLed(LedAndBuzzerController::LED_ON);
}

void _mainPageOnButton3LOW() {
  LedAndBuzzerController::setGreenLed(LedAndBuzzerController::LED_OFF);
}

void _mainPageOnButton4HIGH() {
  _mainPage->changePage(2);
}

void _mainPageOnButton5HIGH() {
  LCDController::lock();
}

void MainPage::init(PageChangeFunction* pageChangeFunction) {
  Page::init(pageChangeFunction);
  _mainPage = this;

  this->mSecondTimeChangedCallbackController = TimeController::createAndAddSecondListener(_mainPageOnSecondTimeChanged);
  this->mMinuteTimeChangedCallbackController = TimeController::createAndAddMinuteListener(_mainPageOnMinutetimeChanged);
  this->mOnAlarmRunCallbackController = TimeController::createAndAddAlarmRunListener(_mainPageOnAlarmRun);
}

void MainPage::apply() {
  PushButtonController::setListener(_mainPageOnButton1HIGH, _mainPageOnButton1LOW, 1);
  PushButtonController::setListener(_mainPageOnButton2HIGH, _mainPageOnButton2LOW, 2);
  PushButtonController::setListener(_mainPageOnButton3HIGH, _mainPageOnButton3LOW, 3);
  PushButtonController::setListener(_mainPageOnButton4HIGH, NULL, 4);
  PushButtonController::setListener(_mainPageOnButton5HIGH, NULL, 5);

  this->start();
}

void MainPage::start() {
  Serial.println("onMainPageStarted");

  this->mSecondTimeChangedCallbackController->enable();
  this->mMinuteTimeChangedCallbackController->enable();
  this->mOnAlarmRunCallbackController->enable();

  TimeController::postInit();
}

void MainPage::stop() {
  this->mSecondTimeChangedCallbackController->disable();
  this->mMinuteTimeChangedCallbackController->disable();
  this->mOnAlarmRunCallbackController->disable();
}

void MainPage::onEnable() {
  this->start();
}

void MainPage::onDisable() {
  this->stop();
}

void MainPage::onLock() {
  this->stop();
}

void MainPage::onUnlock() {
  this->start();
}

#endif