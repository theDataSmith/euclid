/*
--FILE--
Robot.cpp

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

#include "Robot.h"

namespace EuclidRobot
{
	Robot::Robot()
		: led(PIN_LED, PIN_LED_R, PIN_LED_G, PIN_LED_B)
		, sensorArray(N_SENSORS, PIN_SENSORS)
		, leftMotor(PIN_MOTOR_LEFT_FWD, PIN_MOTOR_LEFT_BWD)
		, rightMotor(PIN_MOTOR_RIGHT_FWD, PIN_MOTOR_RIGHT_BWD)
	{
		//Turn on the LED on the Teensy board.
		led.setOn();
	}

	void Robot::countDown()
	{
		//Red
		led.setR(true);
		delay(400);
		led.setR(false);
		delay(200);

		//Red
		led.setR(true);
		delay(400);
		led.setR(false);
		delay(200);

		//Red
		led.setR(true);
		delay(400);
		led.setR(false);
		delay(200);

		//Green!
		led.setG(true);
		delay(800);
		led.setG(false);
		delay(400);
	}

	void Robot::followLine()
	{
		//Set the mode of the motors.
		leftMotor.setMode(COAST);
		rightMotor.setMode(COAST);

		//Initialize the PID Controller.
		PIDController controller(130, 0, 2);
		controller.start(0);

		//Infinite loop.
		while (true)
		{
			/*
			Read the center of the line.
			This value affects the hue of the RGB LED:
			Far Left: Red
			Center: Green
			Far Right: Blue
			*/
			float error = sensorArray.readLineCenter();
			led.setHSV((error + 1) / 3.0f, 1, 1);

			/*
			Get the correction from the controller.
			*/
			float correction = controller.getCorrection(error);

			/*
			Set the turning of the bot based on this correction.
			*/
			moveForward(1, correction);
			delay(10);
		}
	}

	void Robot::moveForward(float speed, float turning)
	{
		if (turning >= 0)
		{
			//Turn to the right.
			leftMotor.setSpeed(speed);
			rightMotor.setSpeed(speed * (1 - turning));
		}
		else
		{
			//Turn to the left.
			leftMotor.setSpeed(speed * (1 + turning));
			rightMotor.setSpeed(speed);
		}
	}
}