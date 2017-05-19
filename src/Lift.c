#include "Lift.h"
#include "main.h"
#include "ElectricalConstants.h"

bool manual = false;
bool openClaw = false;
bool closeClaw = false;
bool going = false;

void calibrateLiftPot() {
  analogCalibrate(LIFT_POT);
}

int getLiftPot() {
  return analogReadCalibrated(LIFT_POT);
}

void setSpeeds(int x) {
  motorSet(LEFT_TOWER , x);
  motorSet(RIGHT_TOWER, -x);
}

void liftDown() {
  if (manual) {
    setSpeeds(-120);
  } else {
    while(getLiftPot() > 100) {
      setSpeeds(-40);
    }
  }
}

void liftUp() {
  if (manual) {
    motorSet(LEFT_TOWER, 120);
  } else {
    while(getLiftPot() < 1200) {
      setSpeeds(120);
    }
  }
}

void liftLogic() {
  if (joystickGetDigital(1, 5, JOY_UP)) {
    liftUp();
  } else if (joystickGetDigital(1, 5, JOY_DOWN)) {
    liftDown();
  }
}
