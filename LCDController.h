#ifndef LCDController_h
#define LCDController_h

#include <LiquidCrystal.h>


byte degreeChar[8] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte clockChar[8] = {
  B00000,
  B01110,
  B10011,
  B10101,
  B10001,
  B01110,
  B00000,
};

byte doneChar[8] = {
  B00000,
  B00001,
  B00010,
  B10100,
  B01000,
  B00000,
  B00000,
};

byte rightArrowChar[8] = {
  B00000,
  B00100,
  B00010,
  B11111,
  B00010,
  B00100,
  B00000,
};

typedef void (StateChangeListener) (bool, bool);

class LCDController {
  private:
    const static int LCD_WIDTH PROGMEM = 20;
    const static int LCD_HEIGHT PROGMEM = 4;

    const static int LCD_LED_PIN PROGMEM = 49;
    const static int LCD_RS_PIN PROGMEM = 38;
    const static int LCD_ENABLE_PIN PROGMEM = 39;
    const static int LCD_D4_PIN PROGMEM = 40;
    const static int LCD_D5_PIN PROGMEM = 41;
    const static int LCD_D6_PIN PROGMEM = 42;
    const static int LCD_D7_PIN PROGMEM = 43;

    const static int DEGREE_CHAR_CODE PROGMEM = 0;
    const static int CLOCK_CHAR_CODE PROGMEM = 1;
    const static int DONE_CHAR_CODE PROGMEM = 2;
    const static int RIGHT_ARROW_CHAR_CODE PROGMEM = 3;

    static bool isEnabled; // button
    static bool isLocked;
    static LiquidCrystal * lcd;
    static StateChangeListener* onEnableStateChangeListener;
    static StateChangeListener* onLockStateChangeListener;

    static int getMiddleCount(int);
    static void drawMiddle(int, int, bool = true);
    static String getDayOfWeekText(int);
    static void printArrowIfAlarmSelected(int, int);

  public:
    static void init();
    static void update();
    static void clear();
    static void writeTime(String);
    static void writeDate(String, int);
    static void writeHumidity(float);
    static void writeTemperature(float);
    static void writeNextAlarm(Alarm*);
    static void writeFourAlarms(Alarm*, Alarm*, Alarm*, Alarm*, int);
    static void enableLed();
    static void disableLed();
    static void enable();
    static void disable(bool = true);
    static void lock();
    static void unlock();
    static bool getIsAvailable();
    static void startPasswordScreen();
    static void typePassword(int, int);
    static void setOnEnableStateChangeListener(StateChangeListener*);
    static void setOnLockStateChangeListener(StateChangeListener*);
};

bool LCDController::isEnabled = true;
bool LCDController::isLocked = false;
StateChangeListener* LCDController::onEnableStateChangeListener = NULL;
StateChangeListener* LCDController::onLockStateChangeListener = NULL;
LiquidCrystal * LCDController::lcd = new LiquidCrystal(LCDController::LCD_RS_PIN, LCDController::LCD_ENABLE_PIN, LCDController::LCD_D4_PIN, LCDController::LCD_D5_PIN, LCDController::LCD_D6_PIN, LCDController::LCD_D7_PIN);

void LCDController::init() {
  pinMode(LCDController::LCD_LED_PIN, OUTPUT);

  LCDController::lcd->begin(LCDController::LCD_WIDTH, LCDController::LCD_HEIGHT);

  LCDController::lcd->createChar(LCDController::DEGREE_CHAR_CODE, degreeChar);
  LCDController::lcd->createChar(LCDController::CLOCK_CHAR_CODE, clockChar);
  LCDController::lcd->createChar(LCDController::DONE_CHAR_CODE, doneChar);
  LCDController::lcd->createChar(LCDController::RIGHT_ARROW_CHAR_CODE, rightArrowChar);

  LCDController::enable();
  LCDController::lock();
}

void LCDController::update() {

}

void LCDController::clear() {
  LCDController::lcd->clear();
}

int LCDController::getMiddleCount(int count) {
  return (int) ((LCDController::LCD_WIDTH - count) / 2);
}

void LCDController::drawMiddle(int line, int count, bool clear) {
  int middleCount = LCDController::getMiddleCount(count);

  String s;

  if (clear) {
    s = "";

    for (int i = 0; i < LCDController::LCD_WIDTH; i++) {
      s += " ";
    }

    LCDController::lcd->setCursor(0, line);
    LCDController::lcd->print(s);
  }

  s = "";

  for (int i = 0; i < middleCount; i++) {
    s += " ";
  }

  LCDController::lcd->setCursor(0, line);
  LCDController::lcd->print(s);
}

String LCDController::getDayOfWeekText(int dayOfWeek) {
  switch (dayOfWeek) {
    case 0:
      return "Su";

    case 1:
      return "Mo";

    case 2:
      return "Tu";

    case 3:
      return "We";

    case 4:
      return "Th";

    case 5:
      return "Fr";

    case 6:
      return "Sa";
  }

  return "";
}

void LCDController::writeTime(String text) {
  if (LCDController::getIsAvailable()) {
    LCDController::lcd->setCursor(12, 0);
    LCDController::lcd->print(text);
  }
}

void LCDController::writeDate(String text, int dayOfWeek) {
  if (LCDController::getIsAvailable()) {
    LCDController::lcd->setCursor(0, 0);
    LCDController::lcd->print(text);
    LCDController::lcd->print(" ");
    LCDController::lcd->print(LCDController::getDayOfWeekText(dayOfWeek));
  }
}

void LCDController::writeTemperature(float temperature) {
  if (LCDController::getIsAvailable()) {
    LCDController::lcd->setCursor(0, 1);
    LCDController::lcd->print(String(temperature));
    LCDController::lcd->write(byte(LCDController::DEGREE_CHAR_CODE));
    LCDController::lcd->print("C");
  }
}

void LCDController::writeHumidity(float humidity) {
  if (LCDController::getIsAvailable()) {
    LCDController::lcd->setCursor(14, 1);
    LCDController::lcd->print(String(humidity));
    LCDController::lcd->print("%");
  }
}

void LCDController::printArrowIfAlarmSelected(int index, int selectedIndex) {
  if (index == selectedIndex) {
    LCDController::lcd->write(byte(RIGHT_ARROW_CHAR_CODE));
  }
  else {
    LCDController::lcd->print(" ");
  }
}

void LCDController::writeNextAlarm(Alarm* alarm) {
  if (LCDController::getIsAvailable()) {
    LCDController::lcd->setCursor(0, 3);
    LCDController::lcd->print("          ");
    LCDController::lcd->setCursor(0, 3);
    LCDController::lcd->write(byte(LCDController::CLOCK_CHAR_CODE));

    if (alarm != NULL) {
      LCDController::lcd->print(alarm->getAsText());
    }
    else {
      LCDController::lcd->write(byte(LCDController::DONE_CHAR_CODE));
    }

    LCDController::lcd->write(byte(LCDController::RIGHT_ARROW_CHAR_CODE));
    LCDController::lcd->print(String(TimeController::getAlarmCount()));
  }
}

void LCDController::writeFourAlarms(Alarm* alarm1, Alarm* alarm2, Alarm* alarm3, Alarm* alarm4, int selectedIndex) {
  if (LCDController::getIsAvailable()) {
    if (alarm1 != NULL) {
      LCDController::lcd->setCursor(0, 0);
      LCDController::printArrowIfAlarmSelected(0, selectedIndex);
      LCDController::lcd->print(alarm1->getAsText());

      if (alarm2 != NULL) {
          LCDController::lcd->setCursor(0, 1);
          LCDController::printArrowIfAlarmSelected(1, selectedIndex);
          LCDController::lcd->print(alarm2->getAsText());

        if (alarm3 != NULL) {
            LCDController::lcd->setCursor(0, 2);
            LCDController::printArrowIfAlarmSelected(2, selectedIndex);
            LCDController::lcd->print(alarm3->getAsText());

         if (alarm4 != NULL) {
            LCDController::lcd->setCursor(0, 3);
            LCDController::printArrowIfAlarmSelected(3, selectedIndex);
            LCDController::lcd->print(alarm4->getAsText());
          }
        }
      }
    }
  }
}

void LCDController::enableLed() {
  digitalWrite(LCDController::LCD_LED_PIN, LOW);
}

void LCDController::disableLed() {
  digitalWrite(LCDController::LCD_LED_PIN, HIGH);
}

void LCDController::enable() {
  LCDController::isEnabled = true;
  LCDController::lcd->clear();

  LCDController::enableLed();

  if (LCDController::onEnableStateChangeListener != NULL) {
    (*LCDController::onEnableStateChangeListener)(LCDController::isEnabled, LCDController::isLocked);
  }
}

void LCDController::disable(bool disableLed) {
  LCDController::isEnabled = false;
  LCDController::lcd->clear();

  if (disableLed) {
    LCDController::disableLed();
  }

  if (LCDController::onEnableStateChangeListener != NULL) {
    (*LCDController::onEnableStateChangeListener)(LCDController::isEnabled, LCDController::isLocked);
  }
}

void LCDController::lock() {
  LCDController::isLocked = true;
  LCDController::lcd->clear();

  if (LCDController::onLockStateChangeListener != NULL) {
    (*LCDController::onLockStateChangeListener)(LCDController::isEnabled, LCDController::isLocked);
  }
}

void LCDController::unlock() {
  LCDController::isLocked = false;
  LCDController::lcd->clear();

  if (LCDController::onLockStateChangeListener != NULL) {
    (*LCDController::onLockStateChangeListener)(LCDController::isEnabled, LCDController::isLocked);
  }
}

bool LCDController::getIsAvailable() {
  return LCDController::isEnabled && !LCDController::isLocked;
}

void LCDController::startPasswordScreen() {
  if (LCDController::isEnabled && LCDController::isLocked) {
    LCDController::lcd->clear();

    LCDController::drawMiddle(1, 8, false);
    LCDController::lcd->print("Password");

    LCDController::drawMiddle(2, 6, false);
    LCDController::lcd->print("______");
  }
}

void LCDController::typePassword(int starCount, int blankCount) {
  if (LCDController::isEnabled && LCDController::isLocked) {
    LCDController::drawMiddle(2, 6, false);

    String s = "";
    for (int i = 0; i < starCount; i++) {
      s += "*";
    }
    for (int i = 0; i < blankCount; i++) {
      s += "_";
    }

    LCDController::lcd->print(s);
  }
}

void LCDController::setOnEnableStateChangeListener(StateChangeListener* onEnableStateChangeListener) {
  LCDController::onEnableStateChangeListener = onEnableStateChangeListener;
}

void LCDController::setOnLockStateChangeListener(StateChangeListener* onLockStateChangeListener) {
  LCDController::onLockStateChangeListener = onLockStateChangeListener;
}

#endif
