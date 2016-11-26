#pragma once

namespace EuclidRobot
{
	class LED
	{
	public:
		/*
		Sets the mode of the pins.
		*/
		LED(int pinLED, int pinR, int pinG, int pinB);

		/*
		Turns the LED on the Teensy board on or off.
		*/
		void setOn(bool on = true);
		void setOff(bool off = true);

		/*
		Sets the brightness of the red part of the RGB LED.
		A bool turns it on or off, an int sets the brightness between 0-255,
		and a float sets the brightness between 0-1.
		*/
		void setR(bool on);
		void setR(int value);
		void setR(float value);

		/*
		Sets the brightness of the green part of the RGB LED.
		A bool turns it on or off, an int sets the brightness between 0-255,
		and a float sets the brightness between 0-1.
		*/
		void setG(bool on);
		void setG(int value);
		void setG(float value);

		/*
		Sets the brightness of the blue part of the RGB LED.
		A bool turns it on or off, an int sets the brightness between 0-255,
		and a float sets the brightness between 0-1.
		*/
		void setB(bool on);
		void setB(int value);
		void setB(float value);

		/*
		Sets the brightnesses of all three parts of the RGB LED at once.
		An int should be between 0-255, and a float should be between 0-1.
		*/
		void setRGB(int r, int g, int b);
		void setRGB(float r, float g, float b);

		/*
		Sets the color of the RGB LED by hue, saturation, and value.
		Values between 0-1 should be used.
		*/
		void setHSV(float h, float s, float v);

	private:
		/*
		The pin number of the LED on the Teensy board.
		*/
		int pinLED;

		/*
		The pin numbers of the three parts of the RGB LED.
		*/
		int pinR;
		int pinG;
		int pinB;
	};
}