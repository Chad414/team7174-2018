/*
 * drivetrain.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Chad
 */

#include "WPILib.h"
#include <cmath>
#include "ctre/Phoenix.h"

#ifndef SRC_DRIVETRAIN_H_
#define SRC_DRIVETRAIN_H_

#define LEFT_DRIVE1 0
#define LEFT_DRIVE2 2
#define RIGHT_DRIVE1 1
#define RIGHT_DRIVE2 3

class Drivetrain {
public:
	Drivetrain();
	virtual ~Drivetrain();

	void ArcadeDrive(double speed, double angle);
	void driveForward(double speed);
	void stop();
private:
	WPI_TalonSRX m_lDrive1;
	WPI_TalonSRX m_lDrive2;
	WPI_TalonSRX m_rDrive1;
	WPI_TalonSRX m_rDrive2;

	RobotDrive m_drive;
};

#endif /* SRC_DRIVETRAIN_H_ */
