#include "ReflectanceSensor.h"

namespace EuclidRobot
{
	ReflectanceSensor::ReflectanceSensor(int pin) : pin(pin)
	{
		setHighOutput();
	}

	void ReflectanceSensor::setHighOutput()
	{
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
		if (reading)
		{
			reading = false;
			microsDelayStart = micros();
		}
	}

	void ReflectanceSensor::setLowInput()
	{
		//Get the current time in microseconds.
		unsigned long microsTime = micros();

		//Make sure it's been at least MICROS_MIN_DELAY microseconds since the pin was set HIGH.
		if (microsTime - microsDelayStart < MICROS_MIN_DELAY)
		{
			delayMicroseconds(MICROS_MIN_DELAY + microsDelayStart - microsTime);
		}

		//Put the pin in LOW INPUT mode.
		digitalWrite(pin, LOW);
		pinMode(pin, INPUT);
		reading = true;
	}

	bool ReflectanceSensor::read()
	{
		//If it's not in input mode, return HIGH. Otherwise, return the state of the pin.
		return !reading || digitalRead(pin);
	}

	bool ReflectanceSensor::isReading()
	{
		return reading;
	}
}