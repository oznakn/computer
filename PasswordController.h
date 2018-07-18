#ifndef PasswordController_h
#define PasswordController_h

#include "FileController.h"
#include "LCDController.h"

class PasswordController {
  private:

  public:
    static void init();
    static void update();
    static bool tryPassword(String);
};


void PasswordController::init() {
}

void PasswordController::update() {

}

bool PasswordController::tryPassword(String password) {
  if (true || password.equals(FileController::password)) {
    return true;
  }

  return false;
}

#endif