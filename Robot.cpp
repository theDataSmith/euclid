#include "Robot.h"

namespace EuclidRobot
{
	Robot::Robot()
		: led(PIN_LED, PIN_LED_R, PIN_LED_G, PIN_LED_B)
		, sensorArray(N_SENSORS, PIN_SENSORS)
		, leftMotor(PIN_MOTOR_LEFT_FWD, PIN_MOTOR_LEFT_BWD)
		, rightMotor(PIN_MOTOR_RIGHT_FWD, PIN_MOTOR_RIGHT_BWD)
	{
		led.setOn();
	}

	void Robot::countDown()
	{
		led.setR(true);
		delay(400);
		led.setR(false);
		delay(200);

		led.setR(true);
		delay(400);
		led.setR(false);
		delay(200);

		led.setR(true);
		delay(400);
		led.setR(false);
		delay(200);

		led.setG(true);
		delay(800);
		led.setG(false);
		delay(400);
	}

	void Robot::followLine()
	{
		leftMotor.setMode(BRAKE);
		rightMotor.setMode(COAST);

		PIDController controller(200, 0, 10);
		controller.start(0);

		//Infinite loop.
		while (true)
		{
			float error = sensorArray.readLineCenter();
			led.setHSV((error + 1) / 3.0f, 1, 1);

			float correction = controller.getCorrection(error);

			moveForward(1, correction);
			delay(10);
		}
	}

	void Robot::moveForward(float speed, float turning)
	{
		if (turning >= 0)
		{
			leftMotor.setSpeed(speed);
			rightMotor.setSpeed(speed * (1 - turning));
		}
		else
		{
			leftMotor.setSpeed(speed * (1 + turning));
			rightMotor.setSpeed(speed);
		}
	}
}