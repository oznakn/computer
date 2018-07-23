#ifndef FileController_h
#define FileController_h

#include <SD.h>
#include <SPI.h>

#include "LinkedList.h"

#include "Alarm.h"
#include "TimeController.h"

class FileController {
  private:
    const static String PASSWORD_FILE PROGMEM;
    const static String ALARMS_FILE PROGMEM;

  public:
    static String password;

    static bool init();
    static LinkedList<String>* splitString(String, String);
    static String readFile(String);
    static void writeFile(String, String);
    static LinkedList<String>* readFileByLines(String);
    static bool readPassword();
    static bool readAlarmsFromFile();
    static void writeAlarmsToFile();
};

const String FileController::PASSWORD_FILE = "password";
const String FileController::ALARMS_FILE = "alarms";
String FileController::password = "";

bool FileController::init() {
  if (SD.begin(53)) {
    if (FileController::readPassword() && FileController::readAlarmsFromFile()) {
      return true;
    }
  }

  return false;
}

LinkedList<String>* FileController::splitString(String content, String s) {
  LinkedList<String>* items = new LinkedList<String>;

  if (content.equals("")) return items;

  int start = 0;

  while (content.indexOf(s, start) > -1) {
    int end = content.indexOf(s, start);

    items->add(content.substring(start, end));

    start = end + 1;
  }

  String last = content.substring(start);
  if (!last.equals("")) {
    items->add(last);
  }

  return items;
}

String FileController::readFile(String fileName) {
  File file = SD.open(fileName);

  if (file) {
    String fileContent = "";

    while (file.available()) {
      fileContent += (char) file.read();
    }

    file.close();

    return fileContent;
  }

  return "";
}

void FileController::writeFile(String fileName, String data) {
  if (!SD.exists(fileName) || SD.remove(fileName)) {
    File file = SD.open(fileName, FILE_WRITE);

    if (file) {
      file.print(data);

      file.close();
    }
  }
}

LinkedList<String>* FileController::readFileByLines(String fileName) {
  String content = FileController::readFile(fileName);

  return FileController::splitString(content, "\n");
}

bool FileController::readPassword() {
  FileController::password = FileController::readFile(FileController::PASSWORD_FILE);

  return !FileController::password.equals("");
}

bool FileController::readAlarmsFromFile() {
  String content = FileController::readFile(FileController::ALARMS_FILE);

  LinkedList<String>* lines = FileController::splitString(content, ";");

  for (int i = 0; i < lines->size(); i++) {
    LinkedList<String>* items = FileController::splitString(lines->get(i), ",");

    if (items->size() != 4) return false;

    int hour = items->get(0).toInt();
    int minute = items->get(1).toInt();
    bool oneTime = items->get(2).equals("true");
    int buzzerMode = items->get(3).toInt();

    Alarm* alarm = new Alarm(hour, minute, oneTime, buzzerMode);

    TimeController::addAlarm(alarm);
  }

  return true;
}


void FileController::writeAlarmsToFile() {
  LinkedList<Alarm*>* alarmList = TimeController::getAlarmList();

  String content = "";
  int alarmListSize = alarmList->size();

  for (int i = 0; i < alarmListSize; i++) {
    Alarm* alarm = alarmList->get(i);

    String alarmString = "";
    alarmString += String(alarm->getHour()) + ",";
    alarmString += String(alarm->getMinute()) + ",";
    alarmString += (alarm->getOneTime() ? "true" : "false");
    alarmString += "," + String(alarm->getBuzzerMode());

    content += alarmString;

    if (i < alarmListSize - 1) {
      content += ";";
    }
  }
  Serial.println("Writing to alarms file: " + content);

  FileController::writeFile(FileController::ALARMS_FILE, content);
}

#endif
