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
		float nRead = 0;
		long* microsInputEnds = new long[nSensors];
		long* microsInputs = new long[nSensors];

		long microsInputStart = micros();

		for (int i = 0; i < nSensors; i++)
		{
			sensors[i]->setLowInput();
		}

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

		for (int i = 0; i < nSensors; i++)
		{
			microsInputs[i] = microsInputEnds[i] - microsInputStart - 5 * i;
		}

		delete[] microsInputEnds;

		return microsInputs;
	}
}