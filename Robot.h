#pragma once

#include "LED.h"
#include "SensorArray.h"
#include "Motor.h"
#include "PIDController.h"

namespace EuclidRobot
{
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

	class Robot
	{
	public:

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
		LED led;

		SensorArray sensorArray;

		Motor leftMotor;
		Motor rightMotor;

		void moveForward(float speed, float turning);
	};
}