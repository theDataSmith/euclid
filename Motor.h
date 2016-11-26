#pragma once

namespace EuclidRobot
{
	enum MotorMode {COAST, BRAKE};

	class Motor
	{
	public:
		Motor(int pinFwd, int pinBwd);

		void setMode(MotorMode mode);

	private:
		int pinFwd;
		int pinBwd;

		bool coastMode = true;
	};
}