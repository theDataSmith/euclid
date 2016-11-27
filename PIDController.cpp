/*
--FILE--
PIDController.cpp

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

#include "PIDController.h"
#include <Arduino.h>

namespace EuclidRobot
{
	PIDController::PIDController(float P, float I, float D)
		: P(P), I(I), D(D) { }

	void PIDController::start(float initialError)
	{
		microsLastCorrection = micros();
		lastError = initialError;
	}

	float PIDController::getCorrection(float error)
	{
		/*
		Calculate deltaTime.
		*/
		unsigned long microsTime = micros();
		float deltaTime = (microsTime - microsLastCorrection) / 1000000.0f;
		microsLastCorrection = microsTime;

		/*
		Add error to totalError (multiplied by deltaTime).
		*/
		totalError += error * deltaTime;

		/*
		Calculate corrections.
		*/
		float p = P * error;
		float i = I * totalError;
		float d = D * (error - lastError) / deltaTime;

		/*
		Cache error for next time.
		Used to calculate the derivative term.
		*/
		lastError = error;

		return (p + i + d) / 100;
	}
}