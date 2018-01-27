/*
 * drivetrain.h
 *
 *  Created on: Jan 27, 2018
 *      Author: Chad
 */

#ifndef SRC_DRIVETRAIN_H_
#define SRC_DRIVETRAIN_H_

#define LEFT_DRIVE1 0
#define LEFT_DRIVE2 2
#define RIGHT_DRIVE1 1
#define RIGHT_DRIVE2 3

namespace std {

class Drivetrain {
public:
	Drivetrain();
	virtual ~Drivetrain();

	void driveForward(int speed);
private:

	m_lDrive1 Spark;
	m_lDrive2 Spark;
	m_rDrive1 Spark;
	m_rDrive2 Spark;

};

} /* namespace std */

#endif /* SRC_DRIVETRAIN_H_ */
