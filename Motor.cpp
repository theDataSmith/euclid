/*
--FILE--
Motor.cpp

--AUTHOR--
Name:		Josh Alan
GitHub:		theDataSmith
E-mail:		thedatasmith1@gmail.com

--PROJECT--
Euclid, the line-following robot.
GitHub:		github.com/theDataSmith/euclid

--CREATION DATE--
11 / 26 / 2016
*/

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
			//BRAKE mode:

			if (speed >= 0)
			{
				//Forward:

				analogWrite(pinFwd, 255);
				analogWrite(pinBwd, 255 * (1 - speed));
			}
			else
			{
				//Backward:

				analogWrite(pinFwd, 255 * (1 + speed));
				analogWrite(pinBwd, 255);
			}
		}
		else
		{
			//COAST mode:

			if (speed >= 0)
			{
				//Forward:

				analogWrite(pinFwd, 255 * (speed));
				analogWrite(pinBwd, 0);
			}
			else
			{
				//Backward:

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