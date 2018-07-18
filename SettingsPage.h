#ifndef SettingsPage_h
#define SettingsPage_h

#include "Page.h"

class SettingsPage : public Page {
  public:
    SettingsPage(PageChangeFunction*);
    ~SettingsPage();
    void start();
    void stop();
    void onEnable();
    void onDisable();
};

SettingsPage* _settingsPage;

void _settingsPageOnButton5HIGH() {
  _settingsPage->changePage(1);
}

SettingsPage::SettingsPage(PageChangeFunction* pageChangeFunction) : Page(pageChangeFunction) {
  _settingsPage = this;

  PushButtonController::removeListener(1);
  PushButtonController::removeListener(2);
  PushButtonController::removeListener(3);
  PushButtonController::removeListener(4);
  PushButtonController::setListener(_settingsPageOnButton5HIGH, 5);

  this->start();
}

SettingsPage::~SettingsPage() {
  _settingsPage = NULL;
}

void SettingsPage::start() {

}

void SettingsPage::stop() {

}

void SettingsPage::onEnable() {
}

void SettingsPage::onDisable() {

}

#endif