/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.
 *                                                         */
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

class Robot : public frc::IterativeRobot
{
private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;
	int switchLR= 0;
	int autonCase=0;
	std::string gameData;
	HotJoystick *m_driver;
	Drivetrain *m_drivetrain;
	Timer autonTimer;

/////////////////////////////////////////////////////////////////////////////////////
	int startPosition=0;
/////////////////////////////////////////////////////////////////////////////////////

public:

Robot()
{
	m_driver = new HotJoystick(0);
	m_drivetrain = new Drivetrain();
}

void RobotInit()
{
	autonTimer.Stop();
	autonTimer.Reset();
}

void AutonomousInit() override
{
	autonCase=0;
	m_drivetrain->speedMultiplier=1.0;

	std::string gameData;
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	if(gameData[0] == 'L')
	{
		switchLR=-1;
	}

	else if (gameData[0]=='R')
	{
		switchLR=1;
	}
}

void AutonomousPeriodic() //simpleDrive(positive=forwards, positive=right, time seconds)
{
	m_drivetrain->intake(0.0);
	int x=0;
	if (startPosition == 0) //Start center.
	{
		if (switchLR==1) //Switch Right.
		{
			switch (autonCase)
			{
				case 0:
					x = m_drivetrain->simpleDrive(-0.5, 0.0, 1.5); //Move backwards slightly.
					if (x == 1){autonCase++;}break;

				case 1:
					x=m_drivetrain->simpleDrive(0.0, 0.5, 0.91);//Turn R slightly.
					if (x == 1){autonCase++;}break;

				case 2:
					x=m_drivetrain->simpleDrive(-0.5, 0.0, 1.91); //Move backward.
					if (x == 1){autonCase++;}break;

				case 3:
					x=m_drivetrain->simpleDrive(0.0, -0.5, 0.91); //Turn L slightly.
					if (x == 1){autonCase++;}break;

				case 4:
					x=m_drivetrain->simpleDrive(-0.51, 0.0, 2.21); //Move backward to wall.
					if (x == 1){autonCase++;}break;

				case 5:
					x=m_drivetrain->simpleIntake(-1.0, 0.5); //Launch cube backwards.
					if (x == 1){autonCase++;}break;
			}
		}

		else if (switchLR==-1)//Switch left.
		{
			switch (autonCase)
			{
				case 0:
					x = m_drivetrain->simpleDrive(-0.5, 0.0, 1.3); //Move backwards slightly.
					if (x == 1){autonCase++;}break;

				case 1:
					x=m_drivetrain->simpleDrive(0.0, -0.5, 0.91); //Turn L slightly.
					if (x == 1){autonCase++;}break;

				case 2:
					x=m_drivetrain->simpleDrive(-0.5, 0.0, 2.66); //Move backward.
					if (x == 1){autonCase++;}break;

				case 3:
					x=m_drivetrain->simpleDrive(0.0, 0.5, 1.11); //Turn R slightly.
					if (x == 1){autonCase++;}break;

				case 4:
					x=m_drivetrain->simpleDrive(-0.51, 0.0, 2.91); //Move backward to wall.
					if (x == 1){autonCase++;}break;

				case 5:
					x=m_drivetrain->simpleIntake(-1.0, 0.51); //Launch cube backwards.
					if (x == 1){autonCase++;}break;
			}

		}
	}

	else if (startPosition==-1||startPosition==1) //Start L or R.
	{
		std::cout<<"RL working"<<std::endl;
		if (switchLR==startPosition) //Sides match.
		{
			switch (autonCase)
				{
				case 0:
					x=m_drivetrain->simpleDrive(-0.55, 0.141, 4.11); //Move back.
					if (x == 1){autonCase++;}break;

				case 1:
					x=m_drivetrain->simpleDrive(0.0, -0.5 * startPosition, 1.55); //Turn to switch.
					if (x == 1){autonCase++;}break;

				case 2:
					x=m_drivetrain->simpleDrive(-0.5, 0.0, 1.91); //Move back.
					if (x == 1){autonCase++;}break;

				case 3:
					x=m_drivetrain->simpleIntake(-1.0, 0.5); //Launch cube.
					if (x == 1){autonCase++;}break;
				}
		}

		else //Sides don't match.
		{
			switch (autonCase)
				{
					case 0:
						x=m_drivetrain->simpleDrive(-0.55, 0.141, 4.11); //Move back.
						if (x == 1){autonCase++;}break;
				}
		}
	}
}

void TeleopInit()
{

}

void TeleopPeriodic()
{
	std::cout << "Average Talon Value: " << m_drivetrain->getTalonValues() << std::endl;
	if ((fabs (m_driver->AxisLY()) > 0.1 || fabs(m_driver->AxisRX())) > 0.1 )
	{
		m_drivetrain->ArcadeDrive(m_driver->AxisLY(), -m_driver->AxisRX());
		if((fabs(m_driver->AxisRX())) > 0.5)
		{
			m_drivetrain->intake(0.5);
		}

		else if(((fabs(m_driver->AxisRX())) > .8))
		{
			m_drivetrain->intake(0.75);
		}

		if(m_driver->ButtonA())
		{
			m_drivetrain->potato();
		}

		else if (m_driver->ButtonB())
		{
			m_drivetrain->armYDrop();
		}

		else if (m_driver->ButtonY())
		{
			m_drivetrain->maxPowerLaunch();
		}

		else if (m_driver->ButtonLT())
		{
			m_drivetrain->intake(-0.65);
		}

		else if(m_driver->ButtonRT())
		{
			m_drivetrain->intake(0.85);
		}

		else if(m_driver->ButtonRB())
		{
			m_drivetrain->armYAxis(0.5);
		}

		else if (m_driver->ButtonLB())
		{
			m_drivetrain->armYAxis(-0.25);
		}

		else
		{
			if((fabs(m_driver->AxisRX())) < 0.5)
				{
					m_drivetrain->intake(0.3);
				}

			//m_drivetrain->armYAxis(0.09);
			m_drivetrain->stopArmY();
		}
	}

	else if(m_driver->ButtonA())
		{
			m_drivetrain->potato();
		}
	else if(m_driver->ButtonX())
		{
			m_drivetrain->cubeAutoFix();
		}

	else if (m_driver->ButtonY())
		{
			m_drivetrain->maxPowerLaunch();
		}

	else if (m_driver->ButtonB())
		{
			m_drivetrain->armYDrop();
		}

	else if (m_driver->ButtonLT())
		{
			m_drivetrain->intake(-0.65);
		}

	else if(m_driver->ButtonRT())
		{
			m_drivetrain->intake(0.85);
		}

	else if(m_driver->ButtonRB())
		{
			m_drivetrain->armYAxis(0.5);
		}

	else if (m_driver->ButtonLB())
		{
			m_drivetrain->armYAxis(-0.25);
		}

	else
		{
			m_drivetrain->ArcadeDrive(0.0, 0.0);
			m_drivetrain->intake(0.15);
			//m_drivetrain->armYAxis(0.09);
			m_drivetrain->stopArmY();
		}

}

void TestPeriodic()
{

}

};

START_ROBOT_CLASS(Robot)
