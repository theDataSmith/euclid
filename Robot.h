/*
--FILE--
Robot.h

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

#include "LED.h"
#include "SensorArray.h"
#include "Motor.h"
#include "PIDController.h"

namespace EuclidRobot
{
	/*
	The robot interfaces with each component through one or more pins.
	These pins can be used to send or recieve data, or even power low-power devices, such as LEDs.
	Each pin has a number, and those numbers are defined here.
	*/
	static const int PIN_LED = 13;
	static const int PIN_LED_R = 6;
	static const int PIN_LED_G = 5;
	static const int PIN_LED_B = 4;

	static const int N_SENSORS = 6;
	static const int PIN_SENSORS[] = { 7, 8, 9, 10, 11, 12 };

	static const int PIN_MOTOR_LEFT_FWD = 23;
	static const int PIN_MOTOR_LEFT_BWD = 22;
	static const int PIN_MOTOR_RIGHT_FWD = 20;
	static const int PIN_MOTOR_RIGHT_BWD = 21;

	/*
	This robot will follow a black line on a white surface.
	It has two wheels in the back, each controlled by a motor.
	It uses 6 sensors in the front of the robot to sense the location of the black line.
	It also has an RGB LED for output.
	*/
	class Robot
	{
	public:

		/*
		Initializes hardware objects.
		Turns on the LED on the Teensy board.
		*/
		Robot();

		/*
		Blinks a countdown pattern on the RGB LED.
		*/
		void countDown();

		/*
		Follows a black line on a white surface.
		*/
		void followLine();

	private:
		/*
		This object handles the LED on the Teensy board,
		as well as the RGB LED.
		*/
		LED led;

		/*
		Interfaces with the array of 6 reflectance sensors
		that read the location of the black line.
		*/
		SensorArray sensorArray;

		/*
		These objects interface with the H-bridge motor driver,
		which directly controls the two motors.
		*/
		Motor leftMotor;
		Motor rightMotor;

		/*
		Sets the speed of the two motors.
		speed controls how fast it goes.
		turning lowers the speed of one of the motors to turn it:
		-2: Rotate left in place.
		-1: Turn left.
		0: Straight ahead.
		1: Turn right.
		2: Rotate right in place.
		*/
		void moveForward(float speed, float turning);
	};
}