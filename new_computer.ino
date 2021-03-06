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
#include "PageController.h"

void onSwitchHIGH() {
  LCDController::enable();
  PageController::changePage(0);
}

void onSwitchLOW() {
  LCDController::disable();
}

void alarmHandler(int buzzerMode) {
  LedAndBuzzerController::blinkRedLed();
  LedAndBuzzerController::blinkGreenLed();
  LedAndBuzzerController::blinkBlueLed();

  /* switch (buzzerMode) {
    case 0: LedAndBuzzerController::blinkBuzzer(); break;
    case 1: LedAndBuzzerController::startShortBuzzer(); break;
    case 2: LedAndBuzzerController::startMediumBuzzer(); break;
    case 3: LedAndBuzzerController::startLongBuzzer(); break;
  } */
}

void setup() {
  SerialController::init();
  TimeController::init();

  Alarm::setAlarmHandler(alarmHandler);

  if (!FileController::init()) {
    while(true);
  }

  LCDController::init();
  LedAndBuzzerController::init();
  PushButtonController::init();
  TemperatureController::init();
  PageController::init();

  PushButtonController::setListener(onSwitchHIGH, onSwitchLOW, 0);
  PushButtonController::update();

  PageController::postInit();
}

void loop() {
  SerialController::update();
  TimeController::update();
  LCDController::update();
  PushButtonController::update();
  LedAndBuzzerController::update();
  TemperatureController::update();
  PageController::update();
}


