#include "ReflectanceSensor.h"

using namespace euclidRobot;

static const int PIN_LED = 13;

static const int N_SENSORS = 6;
static const int PIN_SENSORS[N_SENSORS] = { 7, 8, 9, 10, 11, 12 };
ReflectanceSensor sensors[N_SENSORS] = {
	ReflectanceSensor(PIN_SENSORS[0]),
	ReflectanceSensor(PIN_SENSORS[1]),
	ReflectanceSensor(PIN_SENSORS[2]),
	ReflectanceSensor(PIN_SENSORS[3]),
	ReflectanceSensor(PIN_SENSORS[4]),
	ReflectanceSensor(PIN_SENSORS[5]),
};

void setup()
{
	Serial.begin(57600);
	pinMode(PIN_LED, OUTPUT);
	digitalWrite(PIN_LED, HIGH);

	
}

void loop()
{
	unsigned long microsInputStart = micros();
	sensors[0].setLowInput();
	while (sensors[0].read())
	{
		//Wait
	}
	unsigned long microsInputEnd = micros();
	sensors[0].setHighOutput();

	Serial.println(microsInputEnd - microsInputStart);

	delay(200);
}
