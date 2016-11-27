/*
--FILE--
PIDController.h

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

#pragma once

namespace EuclidRobot
{
	/*
	A proportional-integral-derivative (PID) controller uses a known error to calculate a correction.
	This correction can then be fed back into a system to reduce error.
	A PID controller uses the sum of three corrections to calculate the total correction:
	- A correction that is directly proportional to error (P).
	- A correction that is proportional to the total accumulated error (I).
	- A correction that is proportional to the change in error over time (D).
	Three constants are used to fine tune these three corrections.
	For more information on PID Control: https://en.wikipedia.org/wiki/PID_controller
	*/
	class PIDController
	{
	public:

		/*
		Sets the three constants for the controller.
		*/
		PIDController(float P, float I, float D);

		/*
		Initializes the controller with an initial error.
		MUST be called before getCorrection().
		*/
		void start(float initialError);

		/*
		Takes in an error and returns a correction.
		start() MUST be called first.
		*/
		float getCorrection(float error);

	private:

		/*
		The three constants used to fine tune the three corrections.
		*/
		float P, I, D;

		/*
		The total accumulated error, multiplied by deltaTime.
		*/
		double totalError = 0;

		/*
		The most recently recieved error.
		Used to calculate the derivative term.
		*/
		float lastError;
		
		/*
		The time in microseconds the last time getCorrection() was called.
		*/
		unsigned long microsLastCorrection;

	};
}