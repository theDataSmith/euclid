#include "ReflectanceSensor.h"
#include "SensorArray.h"

using namespace EuclidRobot;

static const int PIN_LED = 13;

static const int N_SENSORS = 6;
static const int PIN_SENSORS[N_SENSORS] = { 7, 8, 9, 10, 11, 12 };

SensorArray sensorArray(6, PIN_SENSORS);

void setup()
{
	Serial.begin(57600);
	pinMode(PIN_LED, OUTPUT);
	digitalWrite(PIN_LED, HIGH);
}

void loop()
{
	float center = sensorArray.readLineCenter();
	Serial.println(center*100, 3);

	long* microsInput = sensorArray.readMicros();

	for (int i = 0; i < N_SENSORS; i++)
	{
		//Serial.print(microsInput[i]);
		//Serial.print(", ");
	}
	Serial.println();

	delete[] microsInput;


	delay(200);
}
