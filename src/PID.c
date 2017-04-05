#define abs(a) a<0?-a:a

#include "PID.h"

struct PID PID_gyro, PID_leftDrive, PID_rightDrive, PID_leftClaw, PID_rightClaw;

void pid(struct PID *pid, float p, float i, float d, float min, float max)
{
	pid->p = p;
	pid->i = i;
	pid->d = d;
	pid->max = max;
	pid->min = min;
}

void resetPID(struct PID *pid)
{
	pid->e = 0;
	pid->ePrev = 0;
	pid->eDiff = 0;
	pid->iCounter = 0;
	pid->output = 0;
}

float getValue(struct PID *pid, float input, float target, float feedForward)
{
	if (pid->curTarget != target)
    {
		resetPID(pid);
		pid->curTarget = target;
	}

	pid->e = target - input;
	pid->eDiff = pid->ePrev - pid->e;

	if (abs(pid->e) < 0.5 * target)
    {
        pid->iCounter += pid->e;
	}
	else
	{
		pid->iCounter = 0;
	}

	pid->output = pid->e * pid->p + pid->eDiff * pid->d + pid->iCounter * pid->i + feedForward;

	pid->ePrev = pid->e;

	if (pid->output > pid->max)
    {
		pid->output = pid->max;
	}
	else if (pid->output < pid->min)
	{
		pid->output = pid->min;
	}

	return pid->output;
}

void updatePID(struct PID *pid, float p, float i, float d)
{
	pid->p = p;
	pid->i = i;
	pid->d = d;
}

float getError(struct PID *pid)
{
	return pid->e;
}
