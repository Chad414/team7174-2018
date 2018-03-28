/*
 * drivetrain.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Chad
 *
 *
 */

#include "Drivetrain.h"
#include <iostream>

Drivetrain::Drivetrain()

	:
m_lDrive1(LEFT_DRIVE1),
	m_lDrive2(LEFT_DRIVE2),
	m_rDrive1(RIGHT_DRIVE1),
	m_rDrive2(RIGHT_DRIVE2),
	m_drive(&m_lDrive2, &m_lDrive1, &m_rDrive2, &m_rDrive1),
	frontIntake(forwardIntake),
	armYAxisObject(armYAXIS),
	m_lEncoder(LEFT_ENCODER, LEFT_ENCODER, false),
	m_rEncoder(RIGHT_ENCODER, RIGHT_ENCODER, true),
	m_distancePIDWrapper(this),
	m_anglePIDWrapper(this)
{
	m_drive.SetSafetyEnabled(false);
}


// ---------- Drivetrain Functions ----------

Drivetrain::~Drivetrain() {}
double speedMultiplier;
int loopSecond;
int simpleDriveLoopCounter;
Timer autonTimer;
bool timerCheck= true;
//int autonCase;


void Drivetrain::ArcadeDrive(double speed, double angle)
{
	m_drive.SetSafetyEnabled(true);
	m_drive.ArcadeDrive(speed * speedMultiplier, angle * speedMultiplier);
}

int Drivetrain::simpleDrive(double speed, double angle, double loopSeconds)
{
	if (timerCheck==true)
	{
		autonTimer.Start();
		timerCheck=false;
	}
	m_drive.ArcadeDrive(-speed, -angle);
	intake(0.0);

	if (autonTimer.Get()>loopSeconds)
		{

			m_drive.ArcadeDrive(0.0, 0.0);
			intake(0.0);
			autonTimer.Stop();
			autonTimer.Reset();
			timerCheck=true;
			//autonCase++;
			return 1;
		}

	else
	{
		return 0;
	}
}

int Drivetrain::simpleIntake(double speed, double loopSeconds)
{
	if (timerCheck==true)
	{
		autonTimer.Start();
		timerCheck=false;
	}
	m_drive.ArcadeDrive(0.0, 0.0);
	intake(speed);

	if (autonTimer.Get()>loopSeconds)
		{

			m_drive.ArcadeDrive(0.0, 0.0);
			intake(0.0);
			autonTimer.Stop();
			autonTimer.Reset();
			timerCheck=true;
			//autonCase++;
			return 1;
		}

	else
	{
		return 0;
	}
}

int Drivetrain::simpleArmYAxis(double speed, double loopSeconds)
{
	if (timerCheck==true)
	{
		autonTimer.Start();
		timerCheck=false;
	}
	m_drive.ArcadeDrive(0.0, 0.0);
	intake(0.0);
	armYAxis(speed);

	if (autonTimer.Get()>loopSeconds)
		{
			armYAxis(0.0);
			m_drive.ArcadeDrive(0.0, 0.0);
			intake(0.0);
			autonTimer.Stop();
			autonTimer.Reset();
			timerCheck=true;
			//autonCase++;
			return 1;
		}

	else
	{
		return 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
void Drivetrain::waitTime(int x)
{
	sleep_for(x*1000000000ns);
	sleep_until(system_clock::now() + 1s);

}
void Drivetrain::intake(double inOut)
{
	frontIntake.Set(inOut);

}

void Drivetrain::armYAxis(double upDown)
{
	armYAxisObject.Set(upDown);
}

void Drivetrain::cubeAutoFix()
{
	intake(-0.5);
	waitTime(0.08);

}


void Drivetrain::armYDrop()
{

	armYAxisObject.Set(0.35);

	waitTime(0.025);
	//armYAxisObject.Set(0.0);

	stopArmY();
	intake(-0.5);

	//armYAxisObject.Set(0.0);

}

void Drivetrain::maxPowerLaunch()
{
	intake(-1.0);
}

void Drivetrain::potato()
{
	if(speedMultiplier == 1.0)
	{
		speedMultiplier = .5;
		waitTime(.15);
	}
	else if(speedMultiplier == .5)
	{
		speedMultiplier = 1.0;
		waitTime(.15);
	}
}

void Drivetrain::stopArmY() {
	armYAxisObject.StopMotor();
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
	m_lDrive2.StopMotor();
	m_rDrive1.StopMotor();
	m_rDrive2.StopMotor();
}

void Drivetrain::setTalon(double speed, bool left) { // For testing only
	if (left) {
		m_lDrive1.Set(speed);
	} else {
		m_rDrive1.Set(speed);
	}
}

double Drivetrain::getTalonValues() {
	return ((m_lDrive1.Get() + m_rDrive1.Get()) / 2);
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

