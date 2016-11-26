#pragma once

class LED
{
public:
	LED(int pinLED, int pinR, int pinG, int pinB)
		: pinLED(pinLED), pinR(pinR), pinG(pinG), pinB(pinB) {}
	
	void setOn(bool on = true);
	void setOff(bool off = true);

	void setR(bool on);
	void setR(int value);
	void setR(float value);

	void setG(bool on);
	void setG(int value);
	void setG(float value);

	void setB(bool on);
	void setB(int value);
	void setB(float value);

	void setRGB(int r, int g, int b);
	void setRGB(float r, float g, float b);

	void setHSV(float h, float s, float v);

private:
	int pinLED;
	int pinR;
	int pinG;
	int pinB;
};
