#ifndef AlarmPage_h
#define AlarmPage_h

#include "LinkedList.h"
#include "CallbackController.h"

#include "Page.h"
#include "Alarm.h"

#include "TimeController.h"
#include "PushButtonController.h"
#include "LCDController.h"

class AlarmPage : public Page {
  public:
    LinkedList<Alarm*>* mAlarmList;
    int mSelectedAlarmIndex = 0;
    int mStartAlarmIndex = 0;
    Alarm* mSelectedAlarm;

    void applyChangesOnIndexes();

    int mIsEditing = false;
    bool mHourEditing = false;
    bool mMinuteEditing = false;
    bool mOneTimeModeEditing = false;
    bool mBuzzerModeEditing = false;

    AlarmPage(PageChangeFunction*);
    ~AlarmPage();
    void start();
    void stop();
    void onEnable();
    void onDisable();
    void up();
    void down();
    void printAlarms();
    void toggleEditing();
    void startEditing();
    void stopEditing();
    void printAll();
};

AlarmPage* _alarmPage;

void _alarmPageOnButton1HIGH() {
  _alarmPage->down();
}

void _alarmPageOnButton2HIGH() {
  _alarmPage->up();
}

void _alarmPageOnButton1HIGHWhenEditing() {
  if (_alarmPage->mSelectedAlarm != NULL) {
    if (_alarmPage->mHourEditing) {
      _alarmPage->mSelectedAlarm->increaseHour();
    }
    else if (_alarmPage->mMinuteEditing) {
      _alarmPage->mSelectedAlarm->increaseMinute();
    }
    else if (_alarmPage->mOneTimeModeEditing) {
      _alarmPage->mSelectedAlarm->setOneTime(true);
    }
    else if (_alarmPage->mBuzzerModeEditing) {
      _alarmPage->mSelectedAlarm->setBuzzerMode(_alarmPage->mSelectedAlarm->getBuzzerMode() + 1);
    }

    _alarmPage->printAll();
  }
}

void _alarmPageOnButton2HIGHWhenEditing() {
  if (_alarmPage->mSelectedAlarm != NULL) {
    if (_alarmPage->mHourEditing) {
      _alarmPage->mSelectedAlarm->decreaseHour();
    }
    else if (_alarmPage->mMinuteEditing) {
      _alarmPage->mSelectedAlarm->decreaseMinute();
    }
    else if (_alarmPage->mOneTimeModeEditing) {
      _alarmPage->mSelectedAlarm->setOneTime(false);
    }
    else if (_alarmPage->mBuzzerModeEditing) {
      _alarmPage->mSelectedAlarm->setBuzzerMode(_alarmPage->mSelectedAlarm->getBuzzerMode() - 1);
    }

    _alarmPage->printAll();
  }
}

void _alarmPageOnButton4HIGHWhenEditing() {
  if (_alarmPage->mSelectedAlarm != NULL) {
    TimeController::removeAlarm(_alarmPage->mSelectedAlarm); // has auto short

    delete _alarmPage->mSelectedAlarm;

    _alarmPage->mSelectedAlarmIndex = 0;
    _alarmPage->stopEditing();
    _alarmPage->applyChangesOnIndexes();
  }
}

void _alarmPageOnButton3HIGH() {
  _alarmPage->toggleEditing();
}

void _alarmPageOnButton4HIGH() {
  TimeController::createAndAddAlarm(hour(), minute(), true, 0); // has auto short

  _alarmPage->mSelectedAlarmIndex = 0;
  _alarmPage->applyChangesOnIndexes();

  _alarmPage->printAll();
}

void _alarmPageOnButton5HIGH() {
  _alarmPage->changePage(1);
}

AlarmPage::AlarmPage(PageChangeFunction* pageChangeFunction) : Page(pageChangeFunction) {
  _alarmPage = this;

  this->mAlarmList = TimeController::getAlarmList();
  this->mSelectedAlarm = this->mAlarmList->get(0);

  PushButtonController::setListener(_alarmPageOnButton3HIGH, 3);
  PushButtonController::setListener(_alarmPageOnButton5HIGH, 5);
  this->stopEditing();

  this->start();
}

AlarmPage::~AlarmPage() {
  this->stop();
  _alarmPage = NULL;
}

void AlarmPage::start() {
  this->printAll();
}

void AlarmPage::stop() {
}

void AlarmPage::onEnable() {
  this->start();
}

void AlarmPage::onDisable() {
  this->stop();
}

void AlarmPage::printAlarms() {
  String s1 = "";
  String s2 = "";
  String s3 = "";
  String s4 = "";

  int size = this->mAlarmList->size();

  if (size > this->mStartAlarmIndex + 0) {
    s1 = this->mAlarmList->get(this->mStartAlarmIndex + 0)->getAsText();

    if (size > this->mStartAlarmIndex + 1) {
      s2 = this->mAlarmList->get(this->mStartAlarmIndex + 1)->getAsText();

      if (size > this->mStartAlarmIndex + 2) {
        s3 = this->mAlarmList->get(this->mStartAlarmIndex + 2)->getAsText();

        if (size > this->mStartAlarmIndex +  3) {
          s4 = this->mAlarmList->get(this->mStartAlarmIndex + 3)->getAsText();
        }
      }
    }
  }

  LCDController::writeFourAlarms(s1, s2, s3, s4, this->mSelectedAlarmIndex, this->mIsEditing);
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
  else if (this->mAlarmList->size() > 4 && this->mStartAlarmIndex > this->mAlarmList->size() - 4) {
    this->mStartAlarmIndex = this->mAlarmList->size() - 4;
  }

  if (this->mAlarmList->size() > this->mStartAlarmIndex + this->mSelectedAlarmIndex) {
    this->mSelectedAlarm = this->mAlarmList->get(this->mStartAlarmIndex + this->mSelectedAlarmIndex);
  }
  else {
    this->mSelectedAlarm = NULL;
  }

  this->printAll();
}

void AlarmPage::up() {
  this->mSelectedAlarmIndex++;
  this->applyChangesOnIndexes();
}

void AlarmPage::down() {
  this->mSelectedAlarmIndex--;
  this->applyChangesOnIndexes();
}

void AlarmPage::toggleEditing() {
  if (this->mIsEditing && this->mBuzzerModeEditing) {
    this->stopEditing();
  }
  else if (this->mIsEditing && this->mOneTimeModeEditing) {
    this->mHourEditing = false;
    this->mMinuteEditing = false;
    this->mOneTimeModeEditing = false;
    this->mBuzzerModeEditing = true;

    LCDController::writeEditingMode("EDIT: B");
  }
  else if (this->mIsEditing && this->mMinuteEditing) {
    this->mHourEditing = false;
    this->mMinuteEditing = false;
    this->mOneTimeModeEditing = true;
    this->mBuzzerModeEditing = false;

    LCDController::writeEditingMode("EDIT: O");
  }
  else if (this->mIsEditing && this->mHourEditing) {
    this->mHourEditing = false;
    this->mMinuteEditing = true;
    this->mOneTimeModeEditing = false;
    this->mBuzzerModeEditing = false;

    LCDController::writeEditingMode("EDIT: M");
  }
  else {
    this->startEditing();
  }
}

void AlarmPage::startEditing() {
  this->mIsEditing = true;

  this->mHourEditing = true;
  this->mMinuteEditing = false;
  this->mOneTimeModeEditing = false;
  this->mBuzzerModeEditing = false;

  LCDController::writeEditingMode("EDIT: H");

  PushButtonController::setListener(_alarmPageOnButton1HIGHWhenEditing, 1);
  PushButtonController::setListener(_alarmPageOnButton2HIGHWhenEditing, 2);
  PushButtonController::setListener(_alarmPageOnButton4HIGHWhenEditing, 4);

  this->printAll();
}

void AlarmPage::stopEditing() {
  this->mIsEditing = false;

  this->mHourEditing = false;
  this->mMinuteEditing = false;
  this->mOneTimeModeEditing = false;
  this->mBuzzerModeEditing = false;

  LCDController::writeEditingMode("       ");

  PushButtonController::setListener(_alarmPageOnButton1HIGH, 1);
  PushButtonController::setListener(_alarmPageOnButton2HIGH, 2);
  PushButtonController::setListener(_alarmPageOnButton4HIGH, 4);

  TimeController::sortAlarmList();

  AlarmPage::applyChangesOnIndexes();

  this->printAll();
}

void AlarmPage::printAll() {
  if (this->mSelectedAlarm != NULL) {
    LCDController::writeSelectedAlarm(this->mSelectedAlarm->getAsText(), this->mSelectedAlarm->getOneTime(), this->mSelectedAlarm->getBuzzerMode());
  }
  else {
    LCDController::writeSelectedAlarm("     ", true, 0);
  }

  this->printAlarms();
}

#endif