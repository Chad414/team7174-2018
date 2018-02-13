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
	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {
	}

	void TeleopInit() {}

	void TeleopPeriodic() {
		std::cout << "Average Talon Value: " << m_drivetrain->getTalonValues() << std::endl;
		if (fabs(m_driver->AxisLY()) > 0.2 || fabs(m_driver->AxisRX()) > 0.2) {
			m_drivetrain->ArcadeDrive(m_driver->AxisLY(), -m_driver->AxisRX());
		}
		else if(m_driver->ButtonY())
		{
			m_drivetrain->potato();
		}
		else {
			m_drivetrain->ArcadeDrive(0.0, 0.0);
		}
		/*if (m_driver->ButtonA()) {
			m_drivetrain->setTalon(0.8, true);
			m_drivetrain->setTalon(0.8, false);
		}
		*/
	}

	void TestPeriodic() {}

};

START_ROBOT_CLASS(Robot)
