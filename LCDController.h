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

byte dropChar[8] = {
  B00000,
  B00100,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110,
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

typedef void (StateChangeListener) (bool);

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

    static bool isEnabled; // switch button
    static LiquidCrystal * lcd;
    static StateChangeListener* onEnableStateChangeListener;

    static int getMiddleCount(int);
    static void drawMiddle(int, int, bool = true);
    static String getDayOfWeekText(int);

  public:
    const static int DEGREE_CHAR_CODE PROGMEM = 0;
    const static int CLOCK_CHAR_CODE PROGMEM = 1;
    const static int DONE_CHAR_CODE PROGMEM = 2;
    const static int RIGHT_ARROW_CHAR_CODE PROGMEM = 3;
    const static int DROP_CHAR_CODE PROGMEM = 4;

    static void init();
    static void update();
    static void clear();
    static void writeTime(String);
    static void writeDate(String, int);
    static void writeHumidity(float);
    static void writeTemperature(float);
    static void writeMemoryUsage(int);
    static void writeNextAlarm(Alarm*);
    static void writeMenuOptionsToBottom(String);
    static void writeEditingMode(String);
    static void writeSelectedAlarm(String, bool, int);
    static void writeAlarmListItem(String, int, int, bool);
    static void writeFourAlarms(String, String, String, String, int, bool);
    static void enableLed();
    static void disableLed();
    static void enable();
    static void disable();
    static bool getIsEnabled();
    static void startPasswordScreen();
    static void typePassword(int, int);
    static void setOnEnableStateChangeListener(StateChangeListener*);
};

bool LCDController::isEnabled = true;
StateChangeListener* LCDController::onEnableStateChangeListener = NULL;
LiquidCrystal * LCDController::lcd = new LiquidCrystal(LCDController::LCD_RS_PIN, LCDController::LCD_ENABLE_PIN, LCDController::LCD_D4_PIN, LCDController::LCD_D5_PIN, LCDController::LCD_D6_PIN, LCDController::LCD_D7_PIN);

void LCDController::init() {
  pinMode(LCDController::LCD_LED_PIN, OUTPUT);

  LCDController::lcd->begin(LCDController::LCD_WIDTH, LCDController::LCD_HEIGHT);

  LCDController::lcd->createChar(LCDController::DEGREE_CHAR_CODE, degreeChar);
  LCDController::lcd->createChar(LCDController::CLOCK_CHAR_CODE, clockChar);
  LCDController::lcd->createChar(LCDController::DONE_CHAR_CODE, doneChar);
  LCDController::lcd->createChar(LCDController::RIGHT_ARROW_CHAR_CODE, rightArrowChar);
  LCDController::lcd->createChar(LCDController::DROP_CHAR_CODE, dropChar);

  LCDController::enable();
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
  if (LCDController::getIsEnabled()) {
    LCDController::lcd->setCursor(12, 0);
    LCDController::lcd->print(text);
  }
}

void LCDController::writeDate(String text, int dayOfWeek) {
  if (LCDController::getIsEnabled()) {
    LCDController::lcd->setCursor(0, 0);
    LCDController::lcd->print(text);
    LCDController::lcd->print(" ");
    LCDController::lcd->print(LCDController::getDayOfWeekText(dayOfWeek));
  }
}

void LCDController::writeTemperature(float temperature) {
  if (LCDController::getIsEnabled()) {
    LCDController::lcd->setCursor(0, 1);
    LCDController::lcd->print(String(temperature));
    LCDController::lcd->write(byte(LCDController::DEGREE_CHAR_CODE));
    LCDController::lcd->print("C");
  }
}

void LCDController::writeHumidity(float humidity) {
  if (LCDController::getIsEnabled()) {
    LCDController::lcd->setCursor(13, 1);
    LCDController::lcd->write(byte(LCDController::DROP_CHAR_CODE));
    LCDController::lcd->print(String(humidity));
    LCDController::lcd->print("%");
  }
}

void LCDController::writeMemoryUsage(int memoryUsage) {
  if (LCDController::getIsEnabled()) {
    LCDController::lcd->setCursor(15, 2);
    LCDController::lcd->print("M:");
    LCDController::lcd->print(String(memoryUsage));
    LCDController::lcd->print("%");
  }
}

void LCDController::writeMenuOptionsToBottom(String s) {
  if (LCDController::getIsEnabled()) {
    LCDController::lcd->setCursor(0, 3);
    LCDController::lcd->print(s);
  }
}

void LCDController::writeEditingMode(String s) {
  if (LCDController::getIsEnabled()) {
    LCDController::lcd->setCursor(11, 2);
    LCDController::lcd->print(s);
  }
}

void LCDController::writeNextAlarm(Alarm* alarm) {
  if (LCDController::getIsEnabled()) {
    LCDController::lcd->setCursor(0, 2);
    LCDController::lcd->print("          ");
    LCDController::lcd->setCursor(0, 2);
    LCDController::lcd->print(String(TimeController::getAlarmCount()));
    LCDController::lcd->write(byte(LCDController::CLOCK_CHAR_CODE));
    LCDController::lcd->write(byte(LCDController::RIGHT_ARROW_CHAR_CODE));

    if (alarm != NULL) {
      LCDController::lcd->print(alarm->getAsText());
    }
    else {
      LCDController::lcd->write(byte(LCDController::DONE_CHAR_CODE));
    }
  }
}

void LCDController::writeSelectedAlarm(String alarm, bool oneTime, int buzzerMode) {
  if (LCDController::getIsEnabled()) {
    LCDController::lcd->setCursor(11, 1);
    LCDController::lcd->print(alarm + " ");

    switch (buzzerMode) {
      case 0: LCDController::lcd->print('B'); break;
      case 1: LCDController::lcd->print('S'); break;
      case 2: LCDController::lcd->print('M'); break;
      case 3: LCDController::lcd->print('L'); break;
    }

    if (oneTime) {
      LCDController::lcd->print(" ");
    }
    else {
      LCDController::lcd->print("*");
    }
  }
}

void LCDController::writeAlarmListItem(String alarmText, int index, int selectedIndex, bool isEditing) {
  if (!alarmText.equals("")) {
    if (index == selectedIndex) {
      LCDController::lcd->write(byte(RIGHT_ARROW_CHAR_CODE));
      if (isEditing) {
        LCDController::lcd->print(" ");
      }
    }
    else {
      LCDController::lcd->print(" ");
    }

    LCDController::lcd->print(alarmText + " "); // blank for removing digit when editing
  }
  else {
    LCDController::lcd->print("          ");
  }
}

void LCDController::writeFourAlarms(String alarm1, String alarm2, String alarm3, String alarm4, int selectedIndex, bool isEditing) {
  if (LCDController::getIsEnabled()) {
    LCDController::lcd->setCursor(0, 0);
    LCDController::writeAlarmListItem(alarm1, 0, selectedIndex, isEditing);

    LCDController::lcd->setCursor(0, 1);
    LCDController::writeAlarmListItem(alarm2, 1, selectedIndex, isEditing);

    LCDController::lcd->setCursor(0, 2);
    LCDController::writeAlarmListItem(alarm3, 2, selectedIndex, isEditing);

    LCDController::lcd->setCursor(0, 3);
    LCDController::writeAlarmListItem(alarm4, 3, selectedIndex, isEditing);
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
    (*LCDController::onEnableStateChangeListener)(LCDController::isEnabled);
  }
}

void LCDController::disable() {
  LCDController::isEnabled = false;
  LCDController::lcd->clear();
  LCDController::disableLed();

  if (LCDController::onEnableStateChangeListener != NULL) {
    (*LCDController::onEnableStateChangeListener)(LCDController::isEnabled);
  }
}

bool LCDController::getIsEnabled() {
  return LCDController::isEnabled;
}

void LCDController::startPasswordScreen() {
  if (LCDController::getIsEnabled()) {
    LCDController::lcd->clear();

    LCDController::drawMiddle(1, 8, false);
    LCDController::lcd->print("Password");

    LCDController::drawMiddle(2, 4, false);
    LCDController::lcd->print("____"); // TODO
  }
}

void LCDController::typePassword(int starCount, int blankCount) {
  if (LCDController::getIsEnabled()) {
    LCDController::drawMiddle(2, 4, false);

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

#endif
