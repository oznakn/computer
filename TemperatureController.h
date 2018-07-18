#ifndef TemperatureController_h
#define TemperatureController_h

#include <DHT.h>

class TemperatureController {
  private:
    static DHT * dht;

    const static int DHT_PIN PROGMEM = 48;

  public:
    static void init();
    static void update();
    static float getTemperature();
    static float getHumidity();
};

DHT * TemperatureController::dht = new DHT(TemperatureController::DHT_PIN, DHT22);

void TemperatureController::init() {
  TemperatureController::dht->begin();
}

void TemperatureController::update() {
}

float TemperatureController::getTemperature() {
  return TemperatureController::dht->readTemperature();
}

float TemperatureController::getHumidity() {
  return TemperatureController::dht->readHumidity();
}

#endif
