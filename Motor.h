/*
--FILE--
Motor.h

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

#pragma once

namespace EuclidRobot
{
	/*
	Each motor can be set to one of two modes: coast or brake.
	In coast mode, the motor uses less power but has less control.
	The motor will turn much more freely when it's not actively being powered.
	In brake mode, the motor uses more power and has more control.
	The motor will resist turning when it's not actively being powered.
	*/
	enum MotorMode {COAST, BRAKE};

	/*
	This class controls a single motor.
	It uses two pins, and can move forward or backward, at varying speeds.
	It can also be set to one of two modes: coast or brake.
	*/
	class Motor
	{
	public:
		/*
		Sets the pins to OUTPUT mode.
		*/
		Motor(int pinFwd, int pinBwd);

		/*
		Sets the speed of the motor, based on a value between -1 and 1.
		1: Forward.
		0: Stationary.
		-1: Backward.
		*/
		void setSpeed(float speed);
		void setSpeed(float speed, MotorMode mode);

		/*
		Changes the mode to either COAST or BRAKE.
		*/
		void setMode(MotorMode mode);

	private:
		/*
		The two output pins of the motor.
		*/
		int pinFwd;
		int pinBwd;

		/*
		False if the motor is in COAST mode.
		True if the motor is in BRAKE mode.
		*/
		bool brakeMode = false;
	};
}