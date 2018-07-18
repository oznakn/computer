#ifndef PageController_h
#define PageController_h

#include "Page.h"
#include "PasswordPage.h"
#include "MainPage.h"
#include "AlarmPage.h"

int _pageControllerActivePageIndex = -1;

MainPage* _pageControllerMainPage = NULL;
PasswordPage* _pageControllerPasswordPage = NULL;
AlarmPage* _pageControllerAlarmPage = NULL;

void _pageControllerChangePage(int pageIndex) {
  if (_pageControllerActivePageIndex != pageIndex) {
    switch (_pageControllerActivePageIndex) {
      case 0:
        delete _pageControllerPasswordPage;
        _pageControllerPasswordPage = NULL;
        break;

      case 1:
        delete _pageControllerMainPage;
        _pageControllerMainPage = NULL;
        break;

      case 2:
        delete _pageControllerAlarmPage;
        _pageControllerAlarmPage = NULL;
        break;
    }

    LCDController::clear();

    _pageControllerActivePageIndex = pageIndex;

    switch (_pageControllerActivePageIndex) {
      case 0:
        _pageControllerPasswordPage = new PasswordPage(_pageControllerChangePage);
        break;

      case 1:
        _pageControllerMainPage = new MainPage(_pageControllerChangePage);
        break;

      case 2:
        _pageControllerAlarmPage = new AlarmPage(_pageControllerChangePage);
        break;
    }
  }
}

void _pageControllerOnEnableStateChange(bool isEnabled) {
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

class PageController {
  public:
    static void init();
    static void update();
    static void lock();
    static void postInit();
    static void changePage(int);
};

void PageController::init() {

}

void PageController::update() {

}

void PageController::lock() {
  PageController::changePage(0);
}

void PageController::postInit() {
  PageController::lock();

  LCDController::setOnEnableStateChangeListener(_pageControllerOnEnableStateChange);
}

void PageController::changePage(int pageIndex) {
  _pageControllerChangePage(pageIndex);
}

#endif