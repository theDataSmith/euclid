#include "Motor.h"
#include <Arduino.h>

namespace EuclidRobot
{
	Motor::Motor(int pinFwd, int pinBwd)
		: pinFwd(pinFwd), pinBwd(pinBwd)
	{
		pinMode(pinFwd, OUTPUT);
		pinMode(pinBwd, OUTPUT);
	}

	void Motor::setSpeed(float speed)
	{
		if (brakeMode)
		{
			if (speed >= 0)
			{
				analogWrite(pinFwd, 255);
				analogWrite(pinBwd, 255 * (1 - speed));
			}
			else
			{
				analogWrite(pinFwd, 255 * (1 + speed));
				analogWrite(pinBwd, 255);
			}
		}
		else
		{
			if (speed >= 0)
			{
				analogWrite(pinFwd, 255 * (speed));
				analogWrite(pinBwd, 0);
			}
			else
			{
				analogWrite(pinFwd, 0);
				analogWrite(pinBwd, 255 * (-speed));
			}
		}
	}

	void Motor::setSpeed(float speed, MotorMode mode)
	{
		setMode(mode);
		setSpeed(speed);
	}

	void Motor::setMode(MotorMode mode)
	{
		brakeMode = bool(mode);
	}
}