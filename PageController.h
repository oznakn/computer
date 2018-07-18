#ifndef PageController_h
#define PageController_h

#include "Page.h"
#include "PasswordPage.h"
#include "MainPage.h"
#include "AlarmsPage.h"
#include "SettingsPage.h"

int _pageControllerActivePageIndex = -1;

MainPage* _pageControllerMainPage = NULL;
PasswordPage* _pageControllerPasswordPage = NULL;
AlarmsPage* _pageControllerAlarmsPage = NULL;
SettingsPage* _pageControllerSettingsPage = NULL;

void _pageControllerChangePage(int pageIndex) {
  if (_pageControllerActivePageIndex != pageIndex) {
    switch (_pageControllerActivePageIndex) {
      case Page::PASSWORD_PAGE:
        delete _pageControllerPasswordPage;
        _pageControllerPasswordPage = NULL;
        break;

      case Page::MAIN_PAGE:
        delete _pageControllerMainPage;
        _pageControllerMainPage = NULL;
        break;

      case Page::ALARMS_PAGE:
        delete _pageControllerAlarmsPage;
        _pageControllerAlarmsPage = NULL;
        break;

      case Page::SETTINGS_PAGE:
        delete _pageControllerSettingsPage;
        _pageControllerSettingsPage = NULL;
        break;
    }

    LCDController::clear();

    _pageControllerActivePageIndex = pageIndex;

    switch (_pageControllerActivePageIndex) {
      case Page::PASSWORD_PAGE:
        _pageControllerPasswordPage = new PasswordPage(_pageControllerChangePage);
        break;

      case Page::MAIN_PAGE:
        _pageControllerMainPage = new MainPage(_pageControllerChangePage);
        break;

      case Page::ALARMS_PAGE:
        _pageControllerAlarmsPage = new AlarmsPage(_pageControllerChangePage);
        break;

      case Page::SETTINGS_PAGE:
        _pageControllerSettingsPage = new SettingsPage(_pageControllerChangePage);
        break;
    }
  }
}

void _pageControllerOnEnableStateChange(bool isEnabled) {
  if (isEnabled) {
    switch (_pageControllerActivePageIndex) {
      case Page::PASSWORD_PAGE:
        _pageControllerPasswordPage->onEnable();
        break;

      case Page::MAIN_PAGE:
        _pageControllerMainPage->onEnable();
        break;

      case Page::ALARMS_PAGE:
        _pageControllerAlarmsPage->onEnable();
        break;

      case Page::SETTINGS_PAGE:
        _pageControllerSettingsPage->onEnable();
        break;
    }
  }
  else {
    switch (_pageControllerActivePageIndex) {
      case Page::PASSWORD_PAGE:
        _pageControllerPasswordPage->onDisable();
        break;

      case Page::MAIN_PAGE:
        _pageControllerMainPage->onDisable();
        break;

      case Page::ALARMS_PAGE:
        _pageControllerAlarmsPage->onDisable();
        break;

      case Page::SETTINGS_PAGE:
        _pageControllerSettingsPage->onDisable();
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