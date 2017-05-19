#include "main.h"
#include "ElectricalConstants.h"
#include "DriveTrain.h"

//Kaj Drive

void setLeft(int speed) {
  motorSet(FRONT_LEFT, speed);
  motorSet(BACK_LEFT, speed);
}

void setRight(int speed) {
  motorSet(FRONT_RIGHT, -speed);
  motorSet(BACK_RIGHT, speed);
}

void kajDrive() {
  int y = joystickGetAnalog(1, 3);
  int x = joystickGetAnalog(1, 1);

  setLeft(y + x);
  setRight(y - x);
}
