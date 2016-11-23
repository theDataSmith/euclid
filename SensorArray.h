#pragma once
#include "ReflectanceSensor.h"
#include <Arduino.h>
#include <vector>

using namespace std;

namespace EuclidRobot
{
	class SensorArray
	{
	public:

		const int MICROS_WHITE[6] = {
		90, 70, 80, 100, 60, 90
		};
		const int MICROS_BLACK[6] =
		{
			500, 600, 800, 850, 480, 750
		};

		SensorArray(int nSensors, const int pins[]);
		~SensorArray();
		
		float readLineCenter();

		float* readReflectances();

		long* readMicros();

	private:

		//The number of sensors in the array.
		int nSensors;

		float* positionalFactors;

		vector<ReflectanceSensor*> sensors = vector<ReflectanceSensor*>();

		float lastCenter = 0;
	};
}