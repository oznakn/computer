#ifndef AlarmsPage_h
#define AlarmsPage_h

#include "LinkedList.h"
#include "CallbackController.h"

#include "Page.h"
#include "Alarm.h"

#include "TimeController.h"
#include "PushButtonController.h"
#include "LCDController.h"

class AlarmsPage : public Page {
  private:
    CallbackController* mOnAlarmRunCallbackController;

  public:
    LinkedList<Alarm*>* mAlarmList;
    int mSelectedAlarmIndex = 0;
    int mStartAlarmIndex = 0;
    Alarm* mSelectedAlarm;

    void applyChangesOnIndexesAndPrint();

    int mIsEditing = false;
    bool mHourEditing = false;
    bool mMinuteEditing = false;
    bool mOneTimeModeEditing = false;
    bool mBuzzerModeEditing = false;

    AlarmsPage(PageChangeFunction*);
    ~AlarmsPage();
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

AlarmsPage* _alarmsPage;

void _alarmsPageOnButton1HIGH() {
  _alarmsPage->down();
}

void _alarmsPageOnButton2HIGH() {
  _alarmsPage->up();
}

void _alarmsPageOnButton1HIGHWhenEditing() {
  if (_alarmsPage->mSelectedAlarm != NULL) {
    if (_alarmsPage->mHourEditing) {
      _alarmsPage->mSelectedAlarm->increaseHour();
    }
    else if (_alarmsPage->mMinuteEditing) {
      _alarmsPage->mSelectedAlarm->increaseMinute();
    }
    else if (_alarmsPage->mOneTimeModeEditing) {
      _alarmsPage->mSelectedAlarm->setOneTime(false);
    }
    else if (_alarmsPage->mBuzzerModeEditing) {
      _alarmsPage->mSelectedAlarm->setBuzzerMode(_alarmsPage->mSelectedAlarm->getBuzzerMode() + 1);
    }

    _alarmsPage->printAll();
  }
}

void _alarmsPageOnButton2HIGHWhenEditing() {
  if (_alarmsPage->mSelectedAlarm != NULL) {
    if (_alarmsPage->mHourEditing) {
      _alarmsPage->mSelectedAlarm->decreaseHour();
    }
    else if (_alarmsPage->mMinuteEditing) {
      _alarmsPage->mSelectedAlarm->decreaseMinute();
    }
    else if (_alarmsPage->mOneTimeModeEditing) {
      _alarmsPage->mSelectedAlarm->setOneTime(true);
    }
    else if (_alarmsPage->mBuzzerModeEditing) {
      _alarmsPage->mSelectedAlarm->setBuzzerMode(_alarmsPage->mSelectedAlarm->getBuzzerMode() - 1);
    }

    _alarmsPage->printAll();
  }
}

void _alarmsPageOnButton4HIGHWhenEditing() {
  if (_alarmsPage->mSelectedAlarm != NULL) {
    TimeController::removeAlarm(_alarmsPage->mSelectedAlarm); // has auto sort

    delete _alarmsPage->mSelectedAlarm;

    _alarmsPage->mSelectedAlarmIndex = 0;
    _alarmsPage->stopEditing();
    _alarmsPage->applyChangesOnIndexesAndPrint();
  }
}

void _alarmsPageOnButton3HIGH() {
  _alarmsPage->toggleEditing();
}

void _alarmsPageOnButton4HIGH() {
  TimeController::createAndAddAlarm(hour(), minute(), true, 0); // has auto sort

  _alarmsPage->mSelectedAlarmIndex = 0;
  _alarmsPage->applyChangesOnIndexesAndPrint();
}

void _alarmsPageOnButton5HIGH() {
  _alarmsPage->changePage(1);
}

void _alarmsPageOnAlarmRun() {
  _alarmsPage->mSelectedAlarmIndex = 0;
  _alarmsPage->applyChangesOnIndexesAndPrint();
}

AlarmsPage::AlarmsPage(PageChangeFunction* pageChangeFunction) : Page(pageChangeFunction) {
  _alarmsPage = this;

  this->mAlarmList = TimeController::getAlarmList();
  this->mSelectedAlarm = this->mAlarmList->get(0);

  this->mOnAlarmRunCallbackController = TimeController::createAndAddOnAlarmRunCallbackController(_alarmsPageOnAlarmRun);

  PushButtonController::setListener(_alarmsPageOnButton3HIGH, 3);
  PushButtonController::setListener(_alarmsPageOnButton5HIGH, 5);
  this->stopEditing();

  this->start();
}

AlarmsPage::~AlarmsPage() {
  this->stop();
  _alarmsPage = NULL;

  TimeController::removeOnAlarmRunCallbackController(this->mOnAlarmRunCallbackController);

  delete this->mOnAlarmRunCallbackController;
}

void AlarmsPage::start() {
  this->mOnAlarmRunCallbackController->enable();

  this->printAll();
}

void AlarmsPage::stop() {
  this->mOnAlarmRunCallbackController->disable();
}

void AlarmsPage::onEnable() {
  this->start();
}

void AlarmsPage::onDisable() {
  this->stop();
}

void AlarmsPage::printAlarms() {
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

void AlarmsPage::applyChangesOnIndexesAndPrint() {
  if (this->mSelectedAlarmIndex > 3) {
    this->mSelectedAlarmIndex = 3;
    this->mStartAlarmIndex++;
  }
  else if (this->mSelectedAlarmIndex > this->mAlarmList->size() - 1) {
    this->mSelectedAlarmIndex = this->mAlarmList->size() - 1;
  }
  else if (this->mSelectedAlarmIndex < 0) {
    this->mSelectedAlarmIndex = 0;
    this->mStartAlarmIndex--;
  }

  if (this->mStartAlarmIndex < 0) {
    this->mStartAlarmIndex = 0;
  }
  else if (this->mAlarmList->size() <= 4) {
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

void AlarmsPage::up() {
  this->mSelectedAlarmIndex++;
  this->applyChangesOnIndexesAndPrint();
}

void AlarmsPage::down() {
  this->mSelectedAlarmIndex--;
  this->applyChangesOnIndexesAndPrint();
}

void AlarmsPage::toggleEditing() {
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

void AlarmsPage::startEditing() {
  this->mIsEditing = true;

  this->mHourEditing = true;
  this->mMinuteEditing = false;
  this->mOneTimeModeEditing = false;
  this->mBuzzerModeEditing = false;

  LCDController::writeEditingMode("EDIT: H");

  PushButtonController::setListener(_alarmsPageOnButton1HIGHWhenEditing, 1);
  PushButtonController::setListener(_alarmsPageOnButton2HIGHWhenEditing, 2);
  PushButtonController::setListener(_alarmsPageOnButton4HIGHWhenEditing, 4);

  this->printAll();
}

void AlarmsPage::stopEditing() {
  this->mIsEditing = false;

  this->mHourEditing = false;
  this->mMinuteEditing = false;
  this->mOneTimeModeEditing = false;
  this->mBuzzerModeEditing = false;

  LCDController::writeEditingMode("       ");

  PushButtonController::setListener(_alarmsPageOnButton1HIGH, 1);
  PushButtonController::setListener(_alarmsPageOnButton2HIGH, 2);
  PushButtonController::setListener(_alarmsPageOnButton4HIGH, 4);

  TimeController::sortAlarmList();

  AlarmsPage::applyChangesOnIndexesAndPrint();

  this->printAll();
}

void AlarmsPage::printAll() {
  if (this->mSelectedAlarm != NULL) {
    LCDController::writeSelectedAlarm(this->mSelectedAlarm->getAsText(), this->mSelectedAlarm->getOneTime(), this->mSelectedAlarm->getBuzzerMode());
  }
  else {
    LCDController::writeSelectedAlarm("No Alarm", true, -1);
  }

  this->printAlarms();
}

#endif