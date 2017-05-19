#include "Claw.h"
#include "ElectricalConstants.h"
#include "Lift.h"
#include "main.h"

bool manual = false;
bool closeClaw = false;
bool going = false;
bool liftUp = false;
bool liftDown = false;

void calibrateLiftPot() { analogCalibrate(LIFT_POT); }

int getLiftPot() { return analogReadCalibrated(LIFT_POT); }

void setSpeeds(int x) {
  motorSet(LEFT_TOWER, x);
  motorSet(RIGHT_TOWER, -x);
}

void liftClawLogic() {
  if (joystickGetDigital(1, 6, JOY_UP)) {
    liftUp = true;
    liftLogic();
    wait(100);
    openClaw = true;
    clawLogic();
  }
  if (joystickGetDigital(1, 6, JOY_DOWN)) {
    liftDown = true;
    liftLogic();
    wait(100);
  }
}

void liftLogic() {
  if (joystickGetDigital(1, 5, JOY_UP) && getLiftPot() < 1500) {
    liftUp = true;
    liftDown = false;
  }
  if (joystickGetDigital(1, 5, JOY_DOWN) && getLiftPot() > 100) {
    liftDown = true;
    liftUp = false;
  }
  if (liftUp) {
    setSpeeds(120);
    if (getLiftPot() > 1500) {
      liftUp = false;
      setSpeeds(0);
    }
  }
  if (liftDown) {
    setSpeeds(-40);
    if (getLiftPot() < 100) {
      liftDown = false;
      setSpeeds(0);
    }
  }
}
