#ifndef FileController_h
#define FileController_h

#include <SD.h>
#include <SPI.h>

class FileController {
  private:

  public:
    static String password;

    static bool init();
};

String FileController::password = "";

bool FileController::init() {
  if (SD.begin(53)) {
    File file = SD.open("password");

    if (file) {
      FileController::password = "";

      while (file.available()) {
        FileController::password += (char) file.read();
      }

      file.close();

      return true;
    }
  }

  return false;
}

#endif
