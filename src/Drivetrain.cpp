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
	//m_lDrive2(LEFT_DRIVE2),
	m_rDrive1(RIGHT_DRIVE1),
	//m_rDrive2(RIGHT_DRIVE2),
	m_drive(m_lDrive1, m_rDrive1),
	m_lEncoder(LEFT_ENCODER, LEFT_ENCODER, false),
	m_rEncoder(RIGHT_ENCODER, RIGHT_ENCODER, true),
	m_distancePIDWrapper(this),
	m_anglePIDWrapper(this)
{
	m_drive.SetSafetyEnabled(false);
}

// ---------- Drivetrain Functions ----------

Drivetrain::~Drivetrain() {}

void Drivetrain::ArcadeDrive(double speed, double angle) {
	m_drive.SetSafetyEnabled(true);
	m_drive.ArcadeDrive(speed, angle);
}

double Drivetrain::getRawEncoderValues() {
	return ((m_lEncoder.Get() + m_rEncoder.Get()) / 2);
}

double Drivetrain::getAverageDistance() {
	return ((getLeftEncoder() + getRightEncoder()) / 2);
}

double Drivetrain::getLeftEncoder() {
	return m_lEncoder.Get() * DRIVE_ENCODER_CONVERSION;
}

double Drivetrain::getRightEncoder() {
	return m_rEncoder.Get() * DRIVE_ENCODER_CONVERSION;
}

void Drivetrain::stop() {
	m_lDrive1.StopMotor();
	//m_lDrive2.StopMotor();
	m_rDrive1.StopMotor();
	//m_rDrive2.StopMotor();
}

void Drivetrain::setSpeed(double speed) {
	ArcadeDrive(speed, m_turn);
}

void Drivetrain::setTurn(double turn) {
	ArcadeDrive(m_speed, turn);
}

void Drivetrain::setDistancePIDSpeed(double speed) {
	distancePIDSpeed = speed;
}

double Drivetrain::getAngle() {
	return 90.0;
}

// ---------- DistancePIDWrapper Functions ----------

Drivetrain::DistancePIDWrapper::DistancePIDWrapper(Drivetrain* drivetrain) {
	m_drivetrain = drivetrain;
}

Drivetrain::DistancePIDWrapper::~DistancePIDWrapper() {
}

double Drivetrain::DistancePIDWrapper::PIDGet () {
	return(m_drivetrain->getAverageDistance() / DRIVE_ENCODER_CONVERSION);
}

void Drivetrain::DistancePIDWrapper::PIDWrite(double output) {
	m_drivetrain->distancePIDOutput = output;
	m_drivetrain->setSpeed(output * m_drivetrain->distancePIDSpeed);
}

// ---------- AnglePIDWrapper Functions ----------

Drivetrain::AnglePIDWrapper::AnglePIDWrapper(Drivetrain* drivetrain) {
	m_drivetrain = drivetrain;
}

Drivetrain::AnglePIDWrapper::~AnglePIDWrapper() {
}

double Drivetrain::AnglePIDWrapper::PIDGet() {
	return m_drivetrain->getAngle();
}

void Drivetrain::AnglePIDWrapper::PIDWrite(double output) {
	m_drivetrain->setTurn(-output * m_drivetrain->turnPIDSpeed);
	m_drivetrain->anglePIDOutput = output;
}

