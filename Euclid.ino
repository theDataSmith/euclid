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

#include "Robot.h"

void setup()
{
	Serial.begin(57600);

	EuclidRobot::Robot robot;

	robot.countDown();
	robot.followLine();
}


void loop()
{

}
