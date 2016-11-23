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
			sensors.push_back(new ReflectanceSensor(pins[i]));

			positionalFactors[i] = 2.0f*i / (nSensors - 1) - 1;
		}
	}

	SensorArray::~SensorArray()
	{
		for (int i = 0; i < nSensors; i++)
		{
			delete sensors[i];
		}
		sensors.clear();

		delete[] positionalFactors;
	}

	float SensorArray::readLineCenter()
	{
		float* reflectances = readReflectances();

		float averagePosition = 0;
		float totalReflectance = 0;

		for (int i = 0; i < nSensors; i++)
		{
			averagePosition += reflectances[i] * positionalFactors[i];
			totalReflectance += reflectances[i];
		}

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