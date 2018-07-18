#ifndef SerialController_h
#define SerialController_h

#include <SoftwareSerial.h>

class SerialController {
  private:
    // static SoftwareSerial * esp8266;

  public:
    static void init();
    static void update();
};


// SoftwareSerial * SerialController::esp8266 = new SoftwareSerial(36, 37);

void SerialController::init() {
  Serial.begin(9600);
  //SerialController::esp8266->begin(115200);
}

void SerialController::update() {
  /* if (Serial.available()) {
    char c = Serial.read();
    Serial.println("Sending data: " + String(c));
    SerialController::esp8266->write(c);
  }
  if (SerialController::esp8266->available()) {
    char c = SerialController::esp8266->read(); // read the next character.
    Serial.write(c);
  } */
}

#endif
