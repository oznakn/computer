#ifndef MainPage_h
#define MainPage_h

#include "MemoryFree.h"

#include "TimeController.h"
#include "LCDController.h"
#include "LedAndBuzzerController.h"
#include "PushButtonController.h"
#include "TemperatureController.h"

#include "Page.h"

const float MAX_MEMORY PROGMEM = 8192;

class MainPage : public Page {
  private:
    const String MENU_OPTIONS PROGMEM = "1\x3\x1";

    CallbackController* mSecondTimeChangedCallbackController;
    CallbackController* mMinuteTimeChangedCallbackController;
    CallbackController* mOnAlarmRunCallbackController;

  public:
    MainPage(PageChangeFunction*);
    ~MainPage();
    void start();
    void stop();
    void onEnable();
    void onDisable();
};

MainPage* _mainPage;

void _mainPageOnSecondTimeChanged() {
  LCDController::writeTime(TimeController::getTimeText());
  LCDController::writeMemoryUsage((int) (((MAX_MEMORY - freeMemory()) / MAX_MEMORY) * 100));
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
  _mainPage->changePage(2);
}

void _mainPageOnButton2HIGH() {
  LedAndBuzzerController::setBuzzer(LedAndBuzzerController::BUZZER_ON);
}

void _mainPageOnButton2LOW() {
  LedAndBuzzerController::setBuzzer(LedAndBuzzerController::BUZZER_OFF);
}

void _mainPageOnButton3HIGH() {
  LedAndBuzzerController::setGreenLed(LedAndBuzzerController::LED_ON);
}

void _mainPageOnButton3LOW() {
  LedAndBuzzerController::setGreenLed(LedAndBuzzerController::LED_OFF);
}

void _mainPageOnButton5HIGH() {
  _mainPage->changePage(0);
}

MainPage::MainPage(PageChangeFunction* pageChangeFunction) : Page(pageChangeFunction) {
  _mainPage = this;

  this->mSecondTimeChangedCallbackController = TimeController::createAndAddSecondCallbackController(_mainPageOnSecondTimeChanged);
  this->mMinuteTimeChangedCallbackController = TimeController::createAndAddMinuteCallbackController(_mainPageOnMinutetimeChanged);
  this->mOnAlarmRunCallbackController = TimeController::createAndAddOnAlarmRunCallbackController(_mainPageOnAlarmRun);

  PushButtonController::setListener(_mainPageOnButton1HIGH, 1);
  PushButtonController::setListener(_mainPageOnButton2HIGH, _mainPageOnButton2LOW, 2);
  PushButtonController::setListener(_mainPageOnButton3HIGH, _mainPageOnButton3LOW, 3);
  PushButtonController::removeListener(4);
  PushButtonController::setListener(_mainPageOnButton5HIGH, 5);

  this->start();
}

MainPage::~MainPage() {
  this->stop();
  _mainPage = NULL;

  TimeController::removeSecondCallbackController(this->mSecondTimeChangedCallbackController);
  TimeController::removeMinuteCallbackController(this->mMinuteTimeChangedCallbackController);
  TimeController::removeOnAlarmRunCallbackController(this->mOnAlarmRunCallbackController);

  delete this->mSecondTimeChangedCallbackController;
  delete this->mMinuteTimeChangedCallbackController;
  delete this->mOnAlarmRunCallbackController;
}

void MainPage::start() {
  this->mSecondTimeChangedCallbackController->enable();
  this->mMinuteTimeChangedCallbackController->enable();
  this->mOnAlarmRunCallbackController->enable();

  Serial.println("selam");
  LCDController::writeMenuOptionsToBottom(MENU_OPTIONS);

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

#endif