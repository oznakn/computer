#ifndef PushButtonController_h
#define PushButtonController_h

#include "LinkedList.h"
#include "CallbackController.h"

#include "TimeController.h"

class PushButtonController {
  private:
    const static int BUTTON1_PIN PROGMEM = A10;
    const static int BUTTON2_PIN PROGMEM = A12;
    const static int BUTTON3_PIN PROGMEM = A14;
    const static int BUTTON4_PIN PROGMEM = A11;
    const static int BUTTON5_PIN PROGMEM = A13;
    const static int SWITCH_PIN PROGMEM = A15;

    static int BUTTON1_STATE;
    static int BUTTON2_STATE;
    static int BUTTON3_STATE;
    static int BUTTON4_STATE;
    static int BUTTON5_STATE;
    static int SWITCH_STATE;

    static CallbackListener* button1ListenerHIGH;
    static CallbackListener* button1ListenerLOW;
    static CallbackListener* button2ListenerHIGH;
    static CallbackListener* button2ListenerLOW;
    static CallbackListener* button3ListenerHIGH;
    static CallbackListener* button3ListenerLOW;
    static CallbackListener* button4ListenerHIGH;
    static CallbackListener* button4ListenerLOW;
    static CallbackListener* button5ListenerHIGH;
    static CallbackListener* button5ListenerLOW;
    static CallbackListener* switchListenerHIGH;
    static CallbackListener* switchListenerLOW;

  public:
    static void init();
    static void update();
    static void setListener(CallbackListener*, CallbackListener*, int);
    static void removeListener(int);
};

int PushButtonController::BUTTON1_STATE = LOW;
int PushButtonController::BUTTON2_STATE = LOW;
int PushButtonController::BUTTON3_STATE = LOW;
int PushButtonController::BUTTON4_STATE = LOW;
int PushButtonController::BUTTON5_STATE = LOW;
int PushButtonController::SWITCH_STATE = LOW;

CallbackListener* PushButtonController::button1ListenerHIGH = NULL;
CallbackListener* PushButtonController::button1ListenerLOW = NULL;
CallbackListener* PushButtonController::button2ListenerHIGH = NULL;
CallbackListener* PushButtonController::button2ListenerLOW = NULL;
CallbackListener* PushButtonController::button3ListenerHIGH = NULL;
CallbackListener* PushButtonController::button3ListenerLOW = NULL;
CallbackListener* PushButtonController::button4ListenerHIGH = NULL;
CallbackListener* PushButtonController::button4ListenerLOW = NULL;
CallbackListener* PushButtonController::button5ListenerHIGH = NULL;
CallbackListener* PushButtonController::button5ListenerLOW = NULL;
CallbackListener* PushButtonController::switchListenerHIGH = NULL;
CallbackListener* PushButtonController::switchListenerLOW = NULL;

bool buttonsFree = true;

void freeButtons() {
  buttonsFree = true;
}

void freezeButtonsAndFreeAfterDelay() {
  buttonsFree = false;

  TimeController::after(150, freeButtons); // to run listener not more than 1 time in one push
}

void PushButtonController::init() {
  pinMode(PushButtonController::SWITCH_PIN, INPUT);
  pinMode(PushButtonController::BUTTON1_PIN, INPUT);
  pinMode(PushButtonController::BUTTON2_PIN, INPUT);
  pinMode(PushButtonController::BUTTON3_PIN, INPUT);
  pinMode(PushButtonController::BUTTON4_PIN, INPUT);
  pinMode(PushButtonController::BUTTON5_PIN, INPUT);

  PushButtonController::SWITCH_STATE = !digitalRead(PushButtonController::SWITCH_PIN);
}

void PushButtonController::update() {
  if (buttonsFree) {
    if (digitalRead(PushButtonController::SWITCH_PIN) != PushButtonController::SWITCH_STATE) {
      int state = digitalRead(PushButtonController::SWITCH_PIN);

      if (state == HIGH && PushButtonController::switchListenerHIGH != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::switchListenerHIGH)();
      }
      else if (state == LOW && PushButtonController::switchListenerLOW != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::switchListenerLOW)();
      }

      PushButtonController::SWITCH_STATE = state;
    }

    if (digitalRead(PushButtonController::BUTTON1_PIN) != PushButtonController::BUTTON1_STATE) {
      int state = digitalRead(PushButtonController::BUTTON1_PIN);

      if (state == HIGH && PushButtonController::button1ListenerHIGH != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::button1ListenerHIGH)();
      }
      else if (state == LOW && PushButtonController::button1ListenerLOW != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::button1ListenerLOW)();
      }

      PushButtonController::BUTTON1_STATE = state;
    }

    if (digitalRead(PushButtonController::BUTTON2_PIN) != PushButtonController::BUTTON2_STATE) {
      int state = digitalRead(PushButtonController::BUTTON2_PIN);

      if (state == HIGH && PushButtonController::button2ListenerHIGH != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::button2ListenerHIGH)();
      }
      else if (state == LOW && PushButtonController::button2ListenerLOW != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::button2ListenerLOW)();
      }

      PushButtonController::BUTTON2_STATE = state;
    }


    if (digitalRead(PushButtonController::BUTTON3_PIN) != PushButtonController::BUTTON3_STATE) {
      int state = digitalRead(PushButtonController::BUTTON3_PIN);

      if (state == HIGH && PushButtonController::button3ListenerHIGH != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::button3ListenerHIGH)();
      }
      else if (state == LOW && PushButtonController::button3ListenerLOW != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::button3ListenerLOW)();
      }

      PushButtonController::BUTTON3_STATE = state;
    }


    if (digitalRead(PushButtonController::BUTTON4_PIN) != PushButtonController::BUTTON4_STATE) {
      int state = digitalRead(PushButtonController::BUTTON4_PIN);

      if (state == HIGH && PushButtonController::button4ListenerHIGH != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::button4ListenerHIGH)();
      }
      else if (state == LOW && PushButtonController::button4ListenerLOW != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::button4ListenerLOW)();
      }

      PushButtonController::BUTTON4_STATE = state;
    }

    if (digitalRead(PushButtonController::BUTTON5_PIN) != PushButtonController::BUTTON5_STATE) {
      int state = digitalRead(PushButtonController::BUTTON5_PIN);

      if (state == HIGH && PushButtonController::button5ListenerHIGH != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::button5ListenerHIGH)();
      }
      else if (state == LOW && PushButtonController::button5ListenerLOW != NULL) {
        freezeButtonsAndFreeAfterDelay();
        (*PushButtonController::button5ListenerLOW)();
      }

      PushButtonController::BUTTON5_STATE = state;
    }
  }
}


void PushButtonController::setListener(CallbackListener* callbackHIGH, CallbackListener* callbackLOW, int button) {
  switch (button) {
    case 0:
      PushButtonController::switchListenerHIGH = callbackHIGH;
      PushButtonController::switchListenerLOW = callbackLOW;
      break;

    case 1:
      PushButtonController::button1ListenerHIGH = callbackHIGH;
      PushButtonController::button1ListenerLOW = callbackLOW;
      break;

    case 2:
      PushButtonController::button2ListenerHIGH = callbackHIGH;
      PushButtonController::button2ListenerLOW = callbackLOW;
      break;

    case 3:
      PushButtonController::button3ListenerHIGH = callbackHIGH;
      PushButtonController::button3ListenerLOW = callbackLOW;
      break;

    case 4:
      PushButtonController::button4ListenerHIGH = callbackHIGH;
      PushButtonController::button4ListenerLOW = callbackLOW;
      break;

    case 5:
      PushButtonController::button5ListenerHIGH = callbackHIGH;
      PushButtonController::button5ListenerLOW = callbackLOW;
      break;
  }
}

void PushButtonController::removeListener(int button) {
  PushButtonController::setListener(NULL, NULL, button);
}

#endif

