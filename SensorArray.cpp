/*
--FILE--
SensorArray.cpp

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

#include "SensorArray.h"
#include <vector>

using namespace std;

namespace EuclidRobot
{
	SensorArray::SensorArray(int nSensors, const int pins[]) : nSensors(nSensors)
	{
		positionalFactors = new float[nSensors];

		for (int i = 0; i < nSensors; i++)
		{
			//Initialize each ReflectanceSensor object.
			sensors.push_back(new ReflectanceSensor(pins[i]));

			//Give each float a value between -1 and 1, evenly spaced.
			positionalFactors[i] = 2.0f*i / (nSensors - 1) - 1;
		}
	}

	SensorArray::~SensorArray()
	{
		//Cleanup!
		for (int i = 0; i < nSensors; i++)
		{
			delete sensors[i];
		}
		sensors.clear();

		delete[] positionalFactors;
	}

	float SensorArray::readLineCenter()
	{
		/*
		Get an array of reflectances between 0 and 1.
		0: Completely white.
		1: Completely black.
		*/
		float* reflectances = readReflectances();

		/*
		The estimated center of the black line.
		It's calculated by taking the sum of
		each measured reflectance, multiplied by its respective positional factor,
		then dividing by the total reflectance.
		*/
		float averagePosition = 0;

		//The sum of the values in the reflectances array.
		float totalReflectance = 0;

		for (int i = 0; i < nSensors; i++)
		{
			averagePosition += reflectances[i] * positionalFactors[i];
			totalReflectance += reflectances[i];
		}

		/*
		If the totalReflectance is less than MIN_TOTAL_REFLECTANCE,
		then we didn't sense a line. That means the line is either
		to the far left, or the far right. We can use the most recently
		found center to determine which one.

		Otherwise, proceed normally, caching the line center.
		*/
		if (totalReflectance < MIN_TOTAL_REFLECTANCE)
		{
			if (lastCenter < 0)
			{
				averagePosition = -1;
			}
			else if (lastCenter > 0)
			{
				averagePosition = 1;
			}
			else
			{
				averagePosition = 0;
			}
		}
		else
		{
			averagePosition /= totalReflectance;
			lastCenter = averagePosition;
		}

		delete[] reflectances;

		return averagePosition;
	}

	float* SensorArray::readReflectances()
	{
		/*
		This function gets the number to microseconds for each sensor to
		fall from HIGH to LOW and translates those into reflectance values
		between 0 and 1. Where 0 is white, and 1 is black.
		*/
		long* microsInputs = readMicros();
		float* reflectances = new float[nSensors];

		for (int i = 0; i < nSensors; i++)
		{
			if (microsInputs[i] < MICROS_WHITE[i])
			{
				reflectances[i] = 0;
			}
			else if (microsInputs[i] > MICROS_BLACK[i])
			{
				reflectances[i] = 1;
			}
			else
			{
				reflectances[i] = microsInputs[i] - MICROS_WHITE[i];
				reflectances[i] /= MICROS_BLACK[i] - MICROS_WHITE[i];
			}
		}

		delete[] microsInputs;

		return reflectances;
	}

	long* SensorArray::readMicros()
	{
		/*
		The number of sensors that have been read.
		When this value reaches nSensors, we're done reading.
		*/
		float nRead = 0;

		/*
		The time in microseconds when each sensor falls from HIGH to LOW.
		*/
		long* microsInputEnds = new long[nSensors];

		/*
		The end time for each sensor minus the start time.
		*/
		long* microsInputs = new long[nSensors];

		/*
		The time in microseconds just before we start reading the sensors.
		*/
		long microsInputStart = micros();

		/*
		Set each input LOW.
		*/
		for (int i = 0; i < nSensors; i++)
		{
			sensors[i]->setLowInput();
		}

		/*
		Once a sensor's input falls from HIGH to LOW, we're done reading that sensor.
		Record the end time, increment nRead, and set the sensor back to HIGH.
		*/
		while (nRead < nSensors)
		{
			for (int i = 0; i < nSensors; i++)
			{
				if (sensors[i]->isReading() && !sensors[i]->read())
				{
					microsInputEnds[i] = micros();
					sensors[i]->setHighOutput();
					nRead++;
				}
			}
		}

		/*
		Calculate the time in microseconds for each sensor from the start and end times.
		*/
		for (int i = 0; i < nSensors; i++)
		{
			microsInputs[i] = microsInputEnds[i] - microsInputStart - 5 * i;
		}

		delete[] microsInputEnds;

		return microsInputs;
	}
}