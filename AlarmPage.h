#ifndef AlarmPage_h
#define AlarmPage_h

#include "Page.h"
#include "Alarm.h"

#include "TimeController.h"
#include "PushButtonController.h"
#include "LCDController.h"

class AlarmPage : public Page {
  private:
    LinkedList<Alarm*>* mAlarmList;
    int mSelectedAlarmIndex = 0;
    int mStartAlarmIndex = 0;
    void printAlarms();
    void applyChangesOnIndexes();

  public:
    void init(PageChangeFunction*);
    void apply();
    void start();
    void stop();
    void onEnable();
    void onDisable();
    void onLock();
    void onUnlock();
    void up();
    void down();
};

AlarmPage* _alarmPage;

void _alarmPageOnButton2HIGH() {
  _alarmPage->down();
}

void _alarmPageOnButton3HIGH() {
  _alarmPage->up();
}

void _alarmPageOnButton5HIGH() {
  _alarmPage->changePage(1);
}

void AlarmPage::init(PageChangeFunction* pageChangeFunction) {
  Page::init(pageChangeFunction);
  _alarmPage = this;

  this->mAlarmList = TimeController::getAlarmList();
}

void AlarmPage::apply() {
  PushButtonController::removeListener(1);
  PushButtonController::removeListener(4);
  PushButtonController::setListener(_alarmPageOnButton2HIGH, NULL, 2);
  PushButtonController::setListener(_alarmPageOnButton3HIGH, NULL, 3);
  PushButtonController::setListener(_alarmPageOnButton5HIGH, NULL, 5);

  this->start();
}

void AlarmPage::start() {
  this->printAlarms();
}

void AlarmPage::stop() {

}

void AlarmPage::onEnable() {
}

void AlarmPage::onDisable() {

}

void AlarmPage::onLock() {

}

void AlarmPage::onUnlock() {

}

void AlarmPage::printAlarms() {
  Alarm* alarm1 = NULL;
  Alarm* alarm2 = NULL;
  Alarm* alarm3 = NULL;
  Alarm* alarm4 = NULL;

  int size = this->mAlarmList->size();

  if (size >= this->mStartAlarmIndex + 1) {
    alarm1 = this->mAlarmList->get(this->mStartAlarmIndex + 0);

    if (size >= this->mStartAlarmIndex + 2) {
      alarm2 = this->mAlarmList->get(this->mStartAlarmIndex + 1);

      if (size >= this->mStartAlarmIndex + 3) {
        alarm3 = this->mAlarmList->get(this->mStartAlarmIndex + 2);

        if (size >= this->mStartAlarmIndex +  4) {
          alarm4 = this->mAlarmList->get(this->mStartAlarmIndex + 3);
        }
      }
    }
  }

  LCDController::writeFourAlarms(alarm1, alarm2, alarm3, alarm4, this->mSelectedAlarmIndex);
}

void AlarmPage::applyChangesOnIndexes() {
  if (this->mSelectedAlarmIndex > 3) {
    this->mSelectedAlarmIndex = 3;
    this->mStartAlarmIndex++;
  }
  else if (this->mSelectedAlarmIndex < 0) {
    this->mSelectedAlarmIndex = 0;
    this->mStartAlarmIndex--;
  }

  if (this->mStartAlarmIndex < 0) {
    this->mStartAlarmIndex = 0;
  }
  else if (this->mStartAlarmIndex > this->mAlarmList->size() - 4) {
    this->mStartAlarmIndex = this->mAlarmList->size() - 4;
  }
}

void AlarmPage::up() {
  this->mSelectedAlarmIndex++;
  this->applyChangesOnIndexes();
  this->printAlarms();
}

void AlarmPage::down() {
  this->mSelectedAlarmIndex--;
  this->applyChangesOnIndexes();
  this->printAlarms();
}

#endif