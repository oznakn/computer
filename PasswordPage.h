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

#include "Page.h"

class PasswordPage : public Page {
  public:
    const static int PASSWORD_LENGTH PROGMEM = 4;

    String mPassword = "";

    PasswordPage(PageChangeFunction*);
    ~PasswordPage();
    void apply();
    void start();
    void stop();
    void onEnable();
    void onDisable();
};

PasswordPage* _passwordPage;

void _passwordPageRefreshPasswordOnScreen() {
  LCDController::typePassword(_passwordPage->mPassword.length(), PasswordPage::PASSWORD_LENGTH - _passwordPage->mPassword.length());
}

void _passwordPagePasswordCheck() {
  if (FileController::password.equals(_passwordPage->mPassword)) {
    _passwordPage->mPassword = "";

    _passwordPage->changePage(1);
  }
  else {
    _passwordPage->mPassword = "";

    _passwordPageRefreshPasswordOnScreen();
  }
}

void _passwordPagePasswordOnType() {
  if (_passwordPage->mPassword.length() > PasswordPage::PASSWORD_LENGTH) {
    _passwordPage->mPassword = _passwordPage->mPassword.substring(PasswordPage::PASSWORD_LENGTH);
  }

  _passwordPageRefreshPasswordOnScreen();
}

void _passwordPagePasswordOnButton1() {
  _passwordPage->mPassword += "A";
  _passwordPagePasswordOnType();
}

void _passwordPagePasswordOnButton2() {
  _passwordPage->mPassword += "B";
  _passwordPagePasswordOnType();
}

void _passwordPagePasswordOnButton3() {
  _passwordPage->mPassword += "C";
  _passwordPagePasswordOnType();
}

void _passwordPagePasswordOnButton4() {
  _passwordPage->mPassword += "D";
  _passwordPagePasswordOnType();
}

void _passwordPagePasswordOnButton5() {
  _passwordPagePasswordCheck();
}

PasswordPage::PasswordPage(PageChangeFunction* pageChangeFunction) : Page(pageChangeFunction) {
  _passwordPage = this;

  PushButtonController::setListener(_passwordPagePasswordOnButton1, NULL, 1);
  PushButtonController::setListener(_passwordPagePasswordOnButton2, NULL, 2);
  PushButtonController::setListener(_passwordPagePasswordOnButton3, NULL, 3);
  PushButtonController::setListener(_passwordPagePasswordOnButton4, NULL, 4);
  PushButtonController::setListener(_passwordPagePasswordOnButton5, NULL, 5);

  this->start();
}

PasswordPage::~PasswordPage() {
  this->stop();
  _passwordPage = NULL;
}

void PasswordPage::start() {
  LCDController::startPasswordScreen();
}

void PasswordPage::stop() {

}

void PasswordPage::onEnable() {
  this->start();
}

void PasswordPage::onDisable() {

}

#endif