#ifndef LedAndBuzzerController_h
#define LedAndBuzzerController_h

#include "LinkedList.h"

#include "TimeController.h"

class LedAndBuzzerController {
  public:
    const static int LED_BLINK_TIME PROGMEM = 700;
    const static int BUZZER_BLINK_TIME PROGMEM = 700;
    const static int BUZZER_SHORT_TIME PROGMEM = 1500;
    const static int BUZZER_MEDIUM_TIME PROGMEM = 3500;
    const static int BUZZER_LONG_TIME PROGMEM = 7000;

    const static int RED_LED_PIN PROGMEM = 44;
    const static int GREEN_LED_PIN PROGMEM = 45;
    const static int BLUE_LED_PIN PROGMEM = 46;
    const static int BUZZER_PIN PROGMEM = 47;

    const static int LED_ON PROGMEM = LOW;
    const static int LED_OFF PROGMEM = HIGH;
    const static int BUZZER_ON PROGMEM = HIGH;
    const static int BUZZER_OFF PROGMEM = LOW;

    static void init();
    static void update();

    static void setRedLed(int);
    static void setBlueLed(int);
    static void setGreenLed(int);
    static void setLed(int, int);
    static void setBuzzer(int);

    static void blinkRedLed();
    static void blinkGreenLed();
    static void blinkBlueLed();
    static void blinkBuzzer();

    static void startShortBuzzer();
    static void startMediumBuzzer();
    static void startLongBuzzer();
};

void LedAndBuzzerController::init() {
  pinMode(LedAndBuzzerController::RED_LED_PIN , OUTPUT);
  pinMode(LedAndBuzzerController::GREEN_LED_PIN , OUTPUT);
  pinMode(LedAndBuzzerController::BLUE_LED_PIN , OUTPUT);
  pinMode(LedAndBuzzerController::BUZZER_PIN , OUTPUT);

  digitalWrite(LedAndBuzzerController::RED_LED_PIN , HIGH);
  digitalWrite(LedAndBuzzerController::GREEN_LED_PIN , HIGH);
  digitalWrite(LedAndBuzzerController::BLUE_LED_PIN , HIGH);
  digitalWrite(LedAndBuzzerController::BUZZER_PIN , LOW);
}

void LedAndBuzzerController::update() {

}

void LedAndBuzzerController::setRedLed(int state) {
  LedAndBuzzerController::setLed(LedAndBuzzerController::RED_LED_PIN, state);
}

void LedAndBuzzerController::setGreenLed(int state) {
  LedAndBuzzerController::setLed(LedAndBuzzerController::GREEN_LED_PIN, state);
}

void LedAndBuzzerController::setBlueLed(int state) {
  LedAndBuzzerController::setLed(LedAndBuzzerController::BLUE_LED_PIN, state);
}

void LedAndBuzzerController::setLed(int pin, int state) {
  digitalWrite(pin, state);
}

void LedAndBuzzerController::setBuzzer(int state) {
  digitalWrite(LedAndBuzzerController::BUZZER_PIN, state);
}

void LedAndBuzzerController::blinkRedLed() {
  TimeController::pulse(LedAndBuzzerController::RED_LED_PIN, LedAndBuzzerController::LED_BLINK_TIME, HIGH);
}

void LedAndBuzzerController::blinkGreenLed() {
  TimeController::pulse(LedAndBuzzerController::GREEN_LED_PIN, LedAndBuzzerController::LED_BLINK_TIME, HIGH);
}

void LedAndBuzzerController::blinkBlueLed() {
  TimeController::pulse(LedAndBuzzerController::BLUE_LED_PIN, LedAndBuzzerController::LED_BLINK_TIME, HIGH);
}

void LedAndBuzzerController::blinkBuzzer() {
  TimeController::pulse(LedAndBuzzerController::BUZZER_PIN, LedAndBuzzerController::BUZZER_BLINK_TIME, LOW);
}

void LedAndBuzzerController::startShortBuzzer() {
  TimeController::pulse(LedAndBuzzerController::BUZZER_PIN, LedAndBuzzerController::BUZZER_SHORT_TIME, LOW);
}

void LedAndBuzzerController::startMediumBuzzer() {
  TimeController::pulse(LedAndBuzzerController::BUZZER_PIN, LedAndBuzzerController::BUZZER_MEDIUM_TIME, LOW);
}

void LedAndBuzzerController::startLongBuzzer() {
  TimeController::pulse(LedAndBuzzerController::BUZZER_PIN, LedAndBuzzerController::BUZZER_LONG_TIME, LOW);
}

#endif

