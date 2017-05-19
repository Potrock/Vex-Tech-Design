#include "Claw.h"
#include "main.h"
#include "ElectricalConstants.h"

bool closeClawCube = false, openClaw = false, closeClawStar = false;

int getClawPot() {
  return analogReadCalibrated(2);
}


void setClaw(int x) {
  motorSet(7, x);
}

void clawLogic() {
  if (joystickGetDigital(1, 8, JOY_RIGHT) && getClawPot() < 3100) {
    closeClawCube = true;
    openClaw = false;
  }
  if (joystickGetDigital(1, 8, JOY_UP) && getClawPot() > 2500) {
    openClaw = true;
    closeClawCube = false;;
    closeClawStar = true;
  }
  if (joystickGetDigital(1, 8, JOY_LEFT) && getClawPot() < 3100) {
    closeClawStar = true;
    openClaw = false;
  }
  if (closeClawCube) {
    setClaw(-80);
    if (getClawPot() > 3300 && getClawPot() < 3400) {
      setClaw(10);
    }
    if (getClawPot() > 3400) {
      closeClawCube = false;
      setClaw(0);
    }
  }
  if (closeClawStar) {
    if (getClawPot() > 3400 > 3500) {
    setClaw(-80);
  }
    if (getClawPot() > 3400 && getClawPot() < 3500) {
      setClaw(-10);
    }
    if (getClawPot() > 3500) {
      closeClawStar = false;
      setClaw(0);
    }
  }
  if (openClaw || position == 1) {
    setClaw(40);
    if (getClawPot() < 2500) {
      openClaw = false;
      setClaw(0);
    }
  }
}
