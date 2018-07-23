#ifndef PageController_h
#define PageController_h

#include "Page.h"
#include "PasswordPage.h"
#include "MainPage.h"
#include "AlarmsPage.h"
#include "SettingsPage.h"


class PageController {
  private:
    static int activePageIndex;
    static Page* activePage;

  public:
    static void init();
    static void update();
    static void lock();
    static void postInit();
    static void changePage(int);
    static void onEnableStateChange(bool);
};

int PageController::activePageIndex = -1;
Page* PageController::activePage = NULL;

void PageController::init() {

}

void PageController::update() {

}

void PageController::lock() {
  PageController::changePage(0);
}

void PageController::postInit() {
  PageController::lock();

  LCDController::setOnEnableStateChangeListener(PageController::onEnableStateChange);
}

void PageController::changePage(int pageIndex) {
  if (PageController::activePageIndex != pageIndex) {
    if (PageController::activePage != NULL) {
      delete PageController::activePage;
      PageController::activePage = NULL;
    }

    LCDController::clear();

    PageController::activePageIndex = pageIndex;

    switch (PageController::activePageIndex) {
      case Page::PASSWORD_PAGE:
        PageController::activePage = new PasswordPage(PageController::changePage);
        break;

      case Page::MAIN_PAGE:
        PageController::activePage = new MainPage(PageController::changePage);
        break;

      case Page::ALARMS_PAGE:
        PageController::activePage = new AlarmsPage(PageController::changePage);
        break;

      case Page::SETTINGS_PAGE:
        PageController::activePage = new SettingsPage(PageController::changePage);
        break;
    }
  }
}

void PageController::onEnableStateChange(bool isEnabled) {
  if (PageController::activePage != NULL) {
    if (isEnabled) {
      PageController::activePage->onEnable();
    }
    else {
      PageController::activePage->onDisable();
    }
  }
}

#endif