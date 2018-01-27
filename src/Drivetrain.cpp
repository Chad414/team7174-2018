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
	m_rDrive2(RIGHT_DRIVE2)
{

}

Drivetrain::~Drivetrain() {}

void Drivetrain::driveForward(int speed) {
	if ((speed >= -1.0) && (speed <= 1.0)) {
		m_lDrive1.Set(speed);
		m_lDrive2.Set(speed);
		m_rDrive1.Set(-speed);
		m_rDrive2.Set(-speed);
	}
}

void Drivetrain::stop() {
	driveForward(0);
}
