#ifndef MenuPage_h
#define MenuPage_h

class MenuPage : public Page {
  MenuPage(PageChangeFunction*);
  ~MenuPage();
  void start();
  void stop();
  void onEnable();
  void onDisable();
};

MenuPage::MenuPage(PageChangeFunction* pageChangeFunction) : Page(pageChangeFunction) {

}

MenuPage::~MenuPage() {

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

#endif