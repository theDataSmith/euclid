/*
--FILE--
ReflectanceSensor.cpp

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

#include "ReflectanceSensor.h"

namespace EuclidRobot
{
	ReflectanceSensor::ReflectanceSensor(int pin) : pin(pin)
	{
		setHighOutput();
	}

	void ReflectanceSensor::setHighOutput()
	{
		//Set the pin to OUTPUT HIGH.
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);

		/*
		Record the time in microseconds so that if we set the pin LOW,
		we can make sure it's been at least MICROS_MIN_DELAY microseconds.
		*/
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