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

	int autonLoopCounter;
	int startPosition=1;
	int switchLR= 0;

	std::string gameData;


	HotJoystick *m_driver;
	Drivetrain *m_drivetrain;


public:

Robot()
{
	m_driver = new HotJoystick(0);
	m_drivetrain = new Drivetrain();
}

void RobotInit()
{

}

void AutonomousInit() override
{
	autonLoopCounter=0;
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

	else
	{
		switchLR=0;
	}

}

void AutonomousPeriodic()//Neg number turns right. Positive goes forward
{
	if (startPosition == 0) {
		if (autonLoopCounter<400)
			{
			//Middle program.
				m_drivetrain->ArcadeDrive(0.4,0.0);
				autonLoopCounter=autonLoopCounter+1;
			}
		else
		{
			m_drivetrain->ArcadeDrive(0.0,0.0);
		}
	}
	else {
		if (autonLoopCounter<60) {
			m_drivetrain->ArcadeDrive(-1.0,0.0);
			autonLoopCounter=autonLoopCounter+1;
		}
		else
		{
			m_drivetrain->ArcadeDrive(0.0,0.0);
		}
	}

	/*if (autonLoopCounter<100)
		{
			m_drivetrain->ArcadeDrive(1.0,0.0);
			autonLoopCounter=autonLoopCounter+1;
		}
	else
		{
			m_drivetrain->ArcadeDrive(0.0,0.0);
		}
//////////////////////////////////////////////////////////////////////////
	if (startPosition==-1)
	{
		if (switchLR==1 || switchLR == -1)
		{
			if (autonLoopCounter<125)
			{
				m_drivetrain->ArcadeDrive(-0.5,0.75*switchLR);
				m_drivetrain->ArcadeDrive(-0.5,0.0);
				autonLoopCounter++;
			}

			else if (autonLoopCounter<50)
			{
				m_drivetrain->ArcadeDrive(-0.5,1.0*switchLR);
			}


			else if (autonLoopCounter<50)
			{
				m_drivetrain->ArcadeDrive(-0.5,1.0*switchLR);
				//m_drivetrain->intake(0.8);
				autonLoopCounter++;
			}

			else
			{
				m_drivetrain->ArcadeDrive(0.0,0.0);
				m_drivetrain->intake(0.0);
			}
		}
	}

	else if (startPosition==0)
	{
		if (switchLR==1 || switchLR == -1)
			{
				if (autonLoopCounter<25)
					{
						m_drivetrain->ArcadeDrive(-0.5,1.0*switchLR);
						//m_drivetrain->intake(0.8);
						autonLoopCounter++;
					}

				else if (autonLoopCounter<50)
					{
					m_drivetrain->ArcadeDrive(-0.5,1.0*switchLR);
					//m_drivetrain->intake(0.8);
					autonLoopCounter++;
					}
				else
					{
						m_drivetrain->ArcadeDrive(0.0,0.0);
							m_drivetrain->intake(0.0);
					}
			}
	}

	else if (startPosition==1)
	{

	}





	if (switchLR==1 || switchLR == -1)
	{
		if (autonLoopCounter<25)
		{
			m_drivetrain->ArcadeDrive(-0.5,1.0*switchLR);
			//m_drivetrain->intake(0.8);




			autonLoopCounter++;
		}

		else if (autonLoopCounter<50)
				{
					m_drivetrain->ArcadeDrive(-0.5,1.0*switchLR);
					//m_drivetrain->intake(0.8);
					autonLoopCounter++;
				}


		else
		{
			m_drivetrain->ArcadeDrive(0.0,0.0);
			m_drivetrain->intake(0.0);
		}
	}
	else
	{
		if (autonLoopCounter<60)
		{
			m_drivetrain->ArcadeDrive(-1.0,0.0);
			autonLoopCounter=autonLoopCounter+1;
		}
		else
		{
			m_drivetrain->ArcadeDrive(0.0,0.0);
			m_drivetrain->intake(0.0);
		}
	}

*/

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
			m_drivetrain->armYAxis(-0.15);
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
			m_drivetrain->armYAxis(-0.15);
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


/*
	startPosition=1;

	if (startPosition==1)//Left
	{
		if (switchLR==1)
		{

		}

		else if (switchLR==2)
		{

		}

		else if (switchLR==0)
		{

		}
	}

	else if (startPosition==2)//Middle
	{
		if (switchLR==1)
		{

		}

		else if (switchLR==2)
		{

		}

		else if (switchLR==0)
		{

		}
	}

	else if (startPosition==2)//Right
	{
		if (switchLR==1)
		{
			if (autonLoopCounter<40)
				{
					m_drivetrain->ArcadeDrive(0.4,0.0);

					autonLoopCounter++;
				}
		}

		else if (switchLR==2)
		{

		}

		else if (switchLR==0)
		{

		}
	}

*/

/*
	if (autonLoopCounter<100)
	{
		m_drivetrain->ArcadeDrive(-1.0,0.0);
		//m_drivetrain->intake(0.8);
		autonLoopCounter=autonLoopCounter+1;
	}

	else
	{
		m_drivetrain->ArcadeDrive(0.0,0.0);
		m_drivetrain->intake(0.0);
	}
*/

