/*
--FILE--
LED.cpp

--AUTHOR--
Name:		Josh Alan
GitHub:		theDataSmith
E-mail:		thedatasmith1@gmail.com

--PROJECT--
Euclid, the line-following robot.
GitHub:		github.com/theDataSmith/euclid

--CREATION DATE--
11 / 26 / 2016
*/

#include "LED.h"
#include <Arduino.h>

namespace EuclidRobot
{
	LED::LED(int pinLED, int pinR, int pinG, int pinB)
		: pinLED(pinLED), pinR(pinR), pinG(pinG), pinB(pinB)
	{
		pinMode(pinLED, OUTPUT);
		pinMode(pinR, OUTPUT);
		pinMode(pinG, OUTPUT);
		pinMode(pinB, OUTPUT);
	}

	void LED::setOn(bool on)
	{
		digitalWrite(pinLED, on);
	}
	void LED::setOff(bool off)
	{
		digitalWrite(pinLED, !off);
	}



	void LED::setR(bool on)
	{
		digitalWrite(pinR, on);
	}
	void LED::setR(int value)
	{
		analogWrite(pinR, value);
	}
	void LED::setR(float value)
	{
		analogWrite(pinR, int(255 * value));
	}



	void LED::setG(bool on)
	{
		digitalWrite(pinG, on);
	}
	void LED::setG(int value)
	{
		analogWrite(pinG, value);
	}
	void LED::setG(float value)
	{
		analogWrite(pinG, int(255 * value));
	}



	void LED::setB(bool on)
	{
		digitalWrite(pinR, on);
	}
	void LED::setB(int value)
	{
		analogWrite(pinB, value);
	}
	void LED::setB(float value)
	{
		analogWrite(pinB, int(255 * value));
	}



	void LED::setRGB(int r, int g, int b)
	{
		setR(r);
		setG(g);
		setB(b);
	}
	void LED::setRGB(float r, float g, float b)
	{
		setR(int(255 * r));
		setG(int(255 * g));
		setB(int(255 * b));
	}



	void LED::setHSV(float h, float s, float v)
	{
		/*
		Three floats between 0-1 that represent the brightness of each color:
		red, green, and blue.
		*/
		float r = 0;
		float g = 0;
		float b = 0;

		/*
		Calculate RGB from the hue.
		*/
		h *= 6;
		int h2 = h;
		h -= h2;
		
		switch (h2)
		{
		case 0:
			r = 1;
			g = h;
			break;
		case 1:
			g = 1;
			r = 1 - h;
			break;
		case 2:
			g = 1;
			b = h;
			break;
		case 3:
			b = 1;
			g = 1 - h;
			break;
		case 4:
			b = 1;
			r = h;
			break;
		case 5:
			r = 1;
			b = 1 - h;
			break;
		}

		/*
		Introduce possible low saturation.
		*/
		r += (1 - s) * (1 - r);
		g += (1 - s) * (1 - g);
		b += (1 - s) * (1 - b);

		/*
		Multiply each float by the value.
		*/
		r *= v;
		g *= v;
		b *= v;

		setRGB(r, g, b);
	}
}