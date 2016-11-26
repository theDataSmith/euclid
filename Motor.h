#pragma once

namespace EuclidRobot
{
	enum MotorMode {COAST, BRAKE};

	class Motor
	{
	public:
		Motor(int pinFwd, int pinBwd);

		void setSpeed(float speed);
		void setSpeed(float speed, MotorMode mode);

		void setMode(MotorMode mode);

	private:
		int pinFwd;
		int pinBwd;

		bool brakeMode = false;
	};
}