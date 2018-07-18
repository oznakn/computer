#ifndef Page_h
#define Page_h


typedef void (PageChangeFunction) (int);

class Page {
  private:
    PageChangeFunction* mPageChangeFunction;

  public:
    Page(PageChangeFunction*);
    ~Page();
    void start();
    void stop();
    void onEnable();
    void onDisable();
    void changePage(int);
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