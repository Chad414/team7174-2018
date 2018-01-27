/*
 * drivetrain.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Chad
 */

#include "Drivetrain.h"
#include <iostream>

Drivetrain::Drivetrain()
	: m_lDrive1(LEFT_DRIVE1),
	m_lDrive2(LEFT_DRIVE2),
	m_rDrive1(RIGHT_DRIVE1),
	m_rDrive2(RIGHT_DRIVE2),
	m_drive(m_lDrive1, m_lDrive2, m_rDrive1, m_rDrive2)
{
	m_drive.SetSafetyEnabled(false);
}

Drivetrain::~Drivetrain() {}

void Drivetrain::ArcadeDrive(double speed, double angle) {
	m_drive.SetSafetyEnabled(true);
	m_drive.ArcadeDrive(speed, angle);
}

/*void Drivetrain::driveForward(double speed) {
	if ((speed >= -1.0) && (speed <= 1.0)) {
		m_lDrive1.Set(speed);
		m_lDrive2.Set(speed);
		m_rDrive1.Set(-speed);
		m_rDrive2.Set(-speed);
		std::cout << m_lDrive1.Get() << std::endl;
	}
}*/

void Drivetrain::stop() {
	m_lDrive1.StopMotor();
	m_lDrive2.StopMotor();
	m_rDrive1.StopMotor();
	m_rDrive2.StopMotor();
}
