#ifndef Button_h
#define Button_h

#include <SPFD5408_Adafruit_TFTLCD.h>

#include "Values.h"

class Button {
public:
  Adafruit_TFTLCD *mTft;

  int mX;
  int mY;
  String mFirstText;
  String mSecondText;

  int mWidth;
  int mHeight;

  boolean isActive = false;
  boolean drawn = false;
  boolean hasTwoText = true;

  Button(Adafruit_TFTLCD *tft,int x , int y , int width , int height , String firstText , String secondText);
  Button(Adafruit_TFTLCD *tft,int x , int y , int width , int height, String text);

  void draw();
  void changeText(String text);
  void reset();
  void touch();
  int getX();
  void setX(int x);
  int getY();
  void setY(int y);
  boolean isPressed(int x , int y);

};

Button::Button(Adafruit_TFTLCD *tft,int x , int y , int width , int height , String firstText , String secondText) {
  this->mTft = tft;
  this->mX = x;
  this->mY = y;
  this->mFirstText = firstText;
  this->mSecondText = secondText;
  this->mWidth = width;
  this->mHeight = height;
}

Button::Button(Adafruit_TFTLCD *tft,int x , int y , int width , int height, String text) {
  this->mTft = tft;
  this->mX = x;
  this->mY = y;
  this->mFirstText = text;
  this->mSecondText = text;
  this->hasTwoText = false;
  this->mWidth = width;
  this->mHeight = height;
}

void Button::draw() {
  if(Values::getSystemActivated()) {
    if(!this->drawn) {
      String text = this->isActive ? this->mSecondText : this->mFirstText;
      this->mTft->fillRect(mX , mY, mWidth , mHeight , Consonants::BUTTONCOLOR);
      this->mTft->drawRect(mX , mY, mWidth, mHeight , Consonants::BUTTONBORDERCOLOR);
      this->mTft->setCursor(mX + Consonants::BUTTONPADDING,mY + Consonants::BUTTONPADDING);
      this->mTft->setTextColor(Consonants::TEXTCOLOR);
      this->mTft->setTextSize(Consonants::TEXTSIZE);
      this->mTft->print(text);
    }
    else if(hasTwoText) {
      String text = !this->isActive ? this->mSecondText : this->mFirstText;
      this->mTft->setCursor(this->mX + Consonants::BUTTONPADDING,this->mY + Consonants::BUTTONPADDING);
      this->mTft->setTextColor(Consonants::BUTTONCOLOR);
      this->mTft->setTextSize(Consonants::TEXTSIZE);
      this->mTft->print(text);

      String text2 = this->isActive ? this->mSecondText : this->mFirstText;
      this->mTft->setCursor(mX + Consonants::BUTTONPADDING,mY + Consonants::BUTTONPADDING);
      this->mTft->setTextColor(Consonants::TEXTCOLOR);
      this->mTft->setTextSize(Consonants::TEXTSIZE);
      this->mTft->print(text2);
    }
    this->drawn = true;
  }
  else {
    this->drawn = false;
  }
}

void Button::changeText(String text) {
  this->drawn = false;
  this->hasTwoText = true;
  this->isActive = true;
  this->mSecondText = text;
  this->draw();
  this->isActive = false;
  this->mFirstText = text;
}

void Button::reset() {
  this->drawn = false;
}

void Button::touch() {
  this->isActive = !isActive;
  this->draw();
}

int Button::getX() {
  return this->mX;
}

void Button::setX(int x) {
  this->mX = x;
}

int Button::getY() {
  return this->mY;
}

void Button::setY(int y) {
  this->mY = y;
}

boolean Button::isPressed(int x , int y) {
  if(x >= this->mX && x <= this->mX + this->mWidth && y >= this->mY && y <= this->mY + this->mHeight) {
    return true;
  }
  else {
    return false;
  }
}


#endif
