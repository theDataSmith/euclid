/*
--FILE--
SensorArray.h

--AUTHOR--
Name:		Josh Alan
GitHub:		theDataSmith
E-mail:		thedatasmith1@gmail.com

--PROJECT--
Euclid, the line-following robot.
GitHub:		github.com/theDataSmith/euclid

--CREATION DATE--
11 / 22 / 2016
*/

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

		/*
		The number of microseconds it takes for each sensor to go from HIGH to LOW on a white surface.
		These values were measured and manually entered.
		*/
		const int MICROS_WHITE[6] = {
		90, 70, 80, 100, 60, 90
		};

		/*
		The number of microseconds it takes for each sensor to go from HIGH to LOW on a white surface.
		These values were measured and manually entered.
		*/
		const int MICROS_BLACK[6] =
		{
			500, 600, 800, 850, 480, 750
		};

		/*
		If the total reflectance is below this value, the line is not detected.
		*/
		const float MIN_TOTAL_REFLECTANCE = 0.2f;

		/*
		Initializes the positionalFactors and the sensors vector.
		*/
		SensorArray(int nSensors, const int pins[]);

		/*
		Deletes the positionalFactors and each sensor, and clears the sensors vector.
		*/
		~SensorArray();
		
		/*
		Returns a value between -1 and 1.
		-1: The line is far left.
		0: The line is dead center.
		1: The line is far right.
		If the bot loses the line, the most recently found
		center is used to guess where the line is.
		*/
		float readLineCenter();

		/*
		Returns an array of values between 0 and 1, one for each sensor.
		0: Completely white.
		1: Completely black.
		*/
		float* readReflectances();

		/*
		Returns an array of longs.
		Each one represents the number of microseconds it took for that sensor to go from HIGH to LOW.
		*/
		long* readMicros();

	private:

		/*
		The number of sensors in the array.
		*/
		int nSensors;

		/*
		An array of values, one for each sensor.
		Each value represents the position of that sensor, evenly spaced between -1 and 1.
		*/
		float* positionalFactors;

		/*
		An array of pointers to the sensor objects in the SensorArray.
		*/
		vector<ReflectanceSensor*> sensors = vector<ReflectanceSensor*>();

		/*
		The most recently found line center.
		Used in case the array loses the line.
		*/
		float lastCenter = 0;
	};
}