/*
--FILE--
Euclid.ino

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
#include "SensorArray.h"

using namespace EuclidRobot;

static const int PIN_LED = 13;
static const int PIN_LED_R = 6;
static const int PIN_LED_G = 5;
static const int PIN_LED_B = 4;

static const int N_SENSORS = 6;
static const int PIN_SENSORS[N_SENSORS] = { 7, 8, 9, 10, 11, 12 };

SensorArray sensorArray(6, PIN_SENSORS);

void setup()
{
	Serial.begin(57600);
	pinMode(PIN_LED, OUTPUT);
	digitalWrite(PIN_LED, HIGH);

	pinMode(PIN_LED_R, OUTPUT);
	pinMode(PIN_LED_G, OUTPUT);
	pinMode(PIN_LED_B, OUTPUT);
}

void setHue(float hue)
{
	hue *= 6;
	int h = int(hue);

	float r = 0;
	float g = 0;
	float b = 0;

	hue -= h;

	switch (h)
	{
	case 0:
		r = 1;
		g = hue;
		break;
	case 1:
		g = 1;
		r = 1 - hue;
		break;
	case 2:
		g = 1;
		b = hue;
		break;
	case 3:
		b = 1;
		g = 1 - hue;
		break;
	case 4:
		b = 1;
		r = hue;
		break;
	case 5:
		r = 1;
		b = 1 - hue;
		break;
	}

	analogWrite(PIN_LED_R, 255 * r);
	analogWrite(PIN_LED_G, 255 * g);
	analogWrite(PIN_LED_B, 255 * b);
}

void loop()
{
	float center = sensorArray.readLineCenter();
	center /= 2.0f;
	center += .5f;
	setHue((2.0f/3.0f)*center);

	//float* reflectances = sensorArray.readReflectances();
	//for (int i = 0; i < N_SENSORS; i++)
	//{
	//	Serial.print(100*reflectances[i], 0);
	//	Serial.print(", ");
	//}
	//Serial.println();
	//delete[] reflectances;

	//long* microsInput = sensorArray.readMicros();
	//for (int i = 0; i < N_SENSORS; i++)
	//{
	//	Serial.print(microsInput[i]);
	//	Serial.print(", ");
	//}
	//Serial.println();
	//delete[] microsInput;


	delay(20);
}
