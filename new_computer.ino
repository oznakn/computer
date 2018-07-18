/**
 * @author Ozan Akın
 */

#include "CallbackController.h"

#include "SerialController.h"
#include "TimeController.h"
#include "LCDController.h"
#include "LedAndBuzzerController.h"
#include "PushButtonController.h"
#include "FileController.h"
#include "TemperatureController.h"
#include "PasswordController.h"
#include "PageController.h"

#include "PasswordPage.h"
#include "MainPage.h"
#include "AlarmPage.h"

void onSwitchHIGH() {
  LCDController::enable();
  PageController::changePage(0);
}

void onSwitchLOW() {
  LCDController::disable();
}

void setup() {
  if (!FileController::init()) {
    while(true);
  }

  SerialController::init();
  TimeController::init();
  PasswordController::init();
  LCDController::init();
  LedAndBuzzerController::init();
  PushButtonController::init();
  TemperatureController::init();
  PageController::init();

  TimeController::createAndAddAlarm(LedAndBuzzerController::blinkGreenLed, 14, 10);
  TimeController::createAndAddAlarm(LedAndBuzzerController::blinkGreenLed, 14, 20);
  TimeController::createAndAddAlarm(LedAndBuzzerController::blinkGreenLed, 14, 30);
  TimeController::createAndAddAlarm(LedAndBuzzerController::blinkGreenLed, 14, 40);
  TimeController::createAndAddAlarm(LedAndBuzzerController::blinkGreenLed, 14, 50);
  TimeController::createAndAddAlarm(LedAndBuzzerController::blinkGreenLed, 15, 10);
  TimeController::createAndAddAlarm(LedAndBuzzerController::blinkGreenLed, 15, 20);
  TimeController::createAndAddAlarm(LedAndBuzzerController::blinkGreenLed, 15, 30);
  TimeController::createAndAddAlarm(LedAndBuzzerController::blinkGreenLed, 15, 40);

  PushButtonController::setListener(onSwitchHIGH, onSwitchLOW, 0);
  PushButtonController::update();

  PageController::postInit();
}

void loop() {
  SerialController::update();
  TimeController::update();
  PasswordController::update();
  LCDController::update();
  PushButtonController::update();
  LedAndBuzzerController::update();
  TemperatureController::update();
  PageController::update();
}


