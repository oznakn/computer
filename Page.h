#ifndef Page_h
#define Page_h

typedef void (PageChangeFunction) (int);

class Page {
  private:
    PageChangeFunction* mPageChangeFunction;

  public:
    void init(PageChangeFunction*);
    void apply();
    void start();
    void stop();
    void onEnable();
    void onDisable();
    void onLock();
    void onUnlock();
    void changePage(int);
};

void Page::init(PageChangeFunction* pageChangeFunction) {
  this->mPageChangeFunction = pageChangeFunction;
}

void Page::apply() {

}

void Page::start() {
}

void Page::stop() {

}

void Page::onEnable() {
}

void Page::onDisable() {

}

void Page::onLock() {

}

void Page::onUnlock() {

}

void Page::changePage(int pageIndex) {
  (*this->mPageChangeFunction)(pageIndex);
}

#endif