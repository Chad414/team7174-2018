/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "WPILib.h"
#include "RobotUtils/RobotUtils.h"
#include "Drivetrain.h"

class Robot : public frc::IterativeRobot {
private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;

	HotJoystick *m_driver;
	Drivetrain *m_drivetrain;

public:

	Robot() {
		m_driver = new HotJoystick(0);
		m_drivetrain = new Drivetrain();
	}

	void RobotInit() {
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {
	}

	void TeleopInit() {}

	void TeleopPeriodic() {
		if (m_driver->ButtonA()) {
			m_drivetrain->driveForward(0.5);
		}
		else if (m_driver->ButtonB()) {
			m_drivetrain->driveForward(-0.5);
		}
		else {
			m_drivetrain->stop();
		}
	}
	void TestPeriodic() {}

};

START_ROBOT_CLASS(Robot)
