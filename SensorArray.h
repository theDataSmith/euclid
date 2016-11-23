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
		200, 250, 150, 80, 80, 80
		};
		const int MICROS_BLACK[6] =
		{
			300, 300, 200, 120, 120, 120
		};

		/*const int MICROS_WHITE[6] = {
			70, 80, 90, 110, 80, 110
		};
		const int MICROS_BLACK[6] =
		{
			525, 600, 820, 820, 375, 700
		};*/

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
	};
}