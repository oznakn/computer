#ifndef Page_h
#define Page_h

typedef void (PageChangeFunction) (int);

class Page {
  private:
    PageChangeFunction* mPageChangeFunction;

  public:
    const static int PASSWORD_PAGE PROGMEM = 0;
    const static int MAIN_PAGE PROGMEM = 1;
    const static int ALARMS_PAGE PROGMEM = 2;
    const static int SETTINGS_PAGE PROGMEM = 3;

    Page(PageChangeFunction*);
    virtual ~Page();
    virtual void start();
    virtual void stop();
    virtual void onEnable();
    virtual void onDisable();
    virtual void changePage(int);
};

Page::Page(PageChangeFunction* pageChangeFunction) {
  this->mPageChangeFunction = pageChangeFunction;
}

Page::~Page() {

}

void Page::start() {

}

void Page::stop() {

}

void Page::onEnable() {
}

void Page::onDisable() {

}

void Page::changePage(int pageIndex) {
  (*this->mPageChangeFunction)(pageIndex);
}

#endif