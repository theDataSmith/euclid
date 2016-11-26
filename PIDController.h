#pragma once

namespace EuclidRobot
{
	class PIDController
	{
	public:

		PIDController(float P, float I, float D);

		void start(float initialError);

		float getCorrection(float error);

	private:

		double totalError = 0;

		float lastError;
		
		unsigned long microsLastCorrection;

	};
}