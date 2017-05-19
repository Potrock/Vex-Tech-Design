#include "Claw.h"
#include "main.h"
#include "ElectricalConstants.h"

bool closeClaw = false, openClaw = false;

int getClawPot() {
  return analogReadCalibrated(2);
}

bool getCloseClaw() {
  if (joystickGetDigital(1, 8, JOY_DOWN) && getClawPot() < 3100) {
    closeClaw = true;
    openClaw = false;
    return true;
  }
  return false;
}

bool getOpenClaw() {
  if (joystickGetDigital(1, 8, JOY_UP) && getClawPot() > 2500) {
    closeClaw = false;
    openClaw = true;
    return true;
  }
  return false;
}

void setClaw(int x) {
  motorSet(7, x);
}

void clawLogic() {
  if (getCloseClaw()) {
    setClaw(-40);
    if (getClawPot() > 3100) {
      closeClaw = false;
      setClaw(0);
    }
  } else if (getOpenClaw()) {
    setClaw(40);
    if (getClawPot() < 2500) {
      openClaw = false;
      setClaw(0);
    }
  }
}
