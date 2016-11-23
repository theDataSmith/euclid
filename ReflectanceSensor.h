#pragma once

#include <Arduino.h>

namespace EuclidRobot
{

	/*
	A class that represents a single reflectance sensor.
	This sensor is a simple device that measures the reflectance of a surface using infrared light.
	A sensor has 1 pin.
	*/
	class ReflectanceSensor
	{
	public:

		//The minimum number of microseconds it takes to properly set the pin HIGH.
		static const int MICROS_MIN_DELAY = 30;

		//Initializes the pin and sets it HIGH.
		ReflectanceSensor(int pin);

		//Sets the pin LOW in INPUT mode.
		void setLowInput();

		//Sets the pin HIGH in OUTPUT mode.
		void setHighOutput();

		//Reads the state of the pin, HIGH or LOW.
		bool read();

		//Returns true if the pin is in INPUT mode.
		bool isReading();

	private:
		//The number for the pin used by the sensor.
		int pin;

		//True if the pin is in INPUT mode.
		bool reading = false;

		//The time (in microseconds) when the pin last switched from INPUT to OUTPUT mode.
		unsigned long microsDelayStart;
	};
}
