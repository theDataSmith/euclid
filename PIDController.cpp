#include "PIDController.h"

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
		unsigned long microsTime = micros();
		float deltaTime = (microsTime - microsLastCorrection) / 1000000;
		microsLastCorrection = microsTime;

		totalError += error * deltaTime;

		float p = P * error;
		float i = I * totalError;
		float d = D * (error - lastError) / deltaTime;

		lastError = error;

		return p + i + d;
	}
}