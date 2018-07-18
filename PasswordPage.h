#ifndef PasswordPage_h
#define PasswordPage_h

#include "CallbackController.h"

#include "SerialController.h"
#include "TimeController.h"
#include "LCDController.h"
#include "LedAndBuzzerController.h"
#include "PushButtonController.h"
#include "FileController.h"
#include "TemperatureController.h"
#include "PasswordController.h"

#include "Page.h"

String _passwordPagePassword = "";

void _passwordPageRefreshPasswordOnScreen() {
  LCDController::typePassword(_passwordPagePassword.length(), 6 - _passwordPagePassword.length());
}

void _passwordPagePasswordCheck() {
  PasswordController::tryPassword(_passwordPagePassword);
  _passwordPagePassword = "";

  _passwordPageRefreshPasswordOnScreen();
}

void _passwordPagePasswordOnType() {
  if (_passwordPagePassword.length() > 6) {
    _passwordPagePassword = _passwordPagePassword.substring(6);
  }

  _passwordPageRefreshPasswordOnScreen();
}

void _passwordPagePasswordOnButton1() {
  _passwordPagePassword += "A";
  _passwordPagePasswordOnType();
}

void _passwordPagePasswordOnButton2() {
  _passwordPagePassword += "B";
  _passwordPagePasswordOnType();
}

void _passwordPagePasswordOnButton3() {
  _passwordPagePassword += "C";
  _passwordPagePasswordOnType();
}

void _passwordPagePasswordOnButton4() {
  _passwordPagePassword += "D";
  _passwordPagePasswordOnType();
}

void _passwordPagePasswordOnButton5() {
  _passwordPagePasswordCheck();
}

class PasswordPage : public Page {
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

void PasswordPage::init(PageChangeFunction* pageChangeFunction) {
  Page::init(pageChangeFunction);
}

void PasswordPage::apply() {
  PushButtonController::setListener(_passwordPagePasswordOnButton1, NULL, 1);
  PushButtonController::setListener(_passwordPagePasswordOnButton2, NULL, 2);
  PushButtonController::setListener(_passwordPagePasswordOnButton3, NULL, 3);
  PushButtonController::setListener(_passwordPagePasswordOnButton4, NULL, 4);
  PushButtonController::setListener(_passwordPagePasswordOnButton5, NULL, 5);

  this->start();
}

void PasswordPage::start() {
  LCDController::startPasswordScreen();
  Serial.println("onPasswordPageStarted");
}

void PasswordPage::stop() {

}

void PasswordPage::onEnable() {
  this->start();
}

void PasswordPage::onDisable() {

}

void PasswordPage::onLock() {

}

void PasswordPage::onUnlock() {

}

#endif