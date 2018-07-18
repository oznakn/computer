#ifndef PageController_h
#define PageController_h

#include "Page.h"
#include "PasswordPage.h"
#include "MainPage.h"
#include "AlarmPage.h"

int _pageControllerActivePageIndex = -1;

MainPage* _pageControllerMainPage;
PasswordPage* _pageControllerPasswordPage;
AlarmPage* _pageControllerAlarmPage;

void _pageControllerChangePage(int pageIndex) {
  switch (_pageControllerActivePageIndex) {
    case 0:
      _pageControllerPasswordPage->stop();
      break;

    case 1:
      _pageControllerMainPage->stop();
      break;

    case 2:
      _pageControllerAlarmPage->stop();
      break;
  }

  _pageControllerActivePageIndex = pageIndex;

  LCDController::clear();

  switch (_pageControllerActivePageIndex) {
    case 0:
      _pageControllerPasswordPage->apply();
      break;

    case 1:
      _pageControllerMainPage->apply();
      break;

    case 2:
      _pageControllerAlarmPage->apply();
      break;
  }
}

void _pageControllerOnEnableStateChange(bool isEnabled, bool isLocked) {
  if (isEnabled) {
    switch (_pageControllerActivePageIndex) {
      case 0:
        _pageControllerPasswordPage->onEnable();
        break;

      case 1:
        _pageControllerMainPage->onEnable();
        break;

      case 2:
        _pageControllerAlarmPage->onEnable();
        break;
    }
  }
  else {
    switch (_pageControllerActivePageIndex) {
      case 0:
        _pageControllerPasswordPage->onDisable();
        break;

      case 1:
        _pageControllerMainPage->onDisable();
        break;

      case 2:
        _pageControllerAlarmPage->onDisable();
        break;
    }
  }
}

void _pageControllerOnLockStateChange(bool isEnabled, bool isLocked) {
  if (isLocked) {
    switch (_pageControllerActivePageIndex) {
      case 0:
        _pageControllerPasswordPage->onLock();
        break;

      case 1:
        _pageControllerMainPage->onLock();
        break;

      case 2:
        _pageControllerAlarmPage->onLock();
        break;
    }

    _pageControllerChangePage(0);
  }
  else {
    switch (_pageControllerActivePageIndex) {
      case 0:
        _pageControllerPasswordPage->onUnlock();
        break;

      case 1:
        _pageControllerMainPage->onUnlock();
        break;

      case 2:
        _pageControllerAlarmPage->onUnlock();
        break;
    }

    _pageControllerChangePage(1);
  }
}

class PageController {
  public:
    static void init();
    static void update();
    static void postInit();
};

void PageController::init() {

}

void PageController::update() {

}

void PageController::postInit() {
  _pageControllerMainPage = new MainPage;
  _pageControllerPasswordPage = new PasswordPage;
  _pageControllerAlarmPage = new AlarmPage;

  _pageControllerMainPage->init(_pageControllerChangePage);
  _pageControllerPasswordPage->init(_pageControllerChangePage);
  _pageControllerAlarmPage->init(_pageControllerChangePage);

  _pageControllerChangePage(0);

  LCDController::setOnEnableStateChangeListener(_pageControllerOnEnableStateChange);
  LCDController::setOnLockStateChangeListener(_pageControllerOnLockStateChange);
}

#endif