/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>
using namespace std;

#include <SmartDashboard/SmartDashboard.h>

void Robot::RobotInit() {
	m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
	m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
	oldTime = 0;
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
	//m_autoSelected = m_chooser.GetSelected();
	m_autoSelected = kAutoNameCustom;
	// m_autoSelected = SmartDashboard::GetString("Auto Selector",
	//		 kAutoNameDefault);
	std::cout << "Auto selected: " << m_autoSelected << std::endl;

	if (m_autoSelected == kAutoNameCustom) {
		// Custom Auto goes here
	} else {
		// Default Auto goes here
	}
	timer.Start();
	cout << deltaTime << endl;
	countdown = 2;
	vitesse = 0.2;
}

void Robot::AutonomousPeriodic() {
	if (m_autoSelected == kAutoNameCustom) {
		// Custom Auto goes here

	Drive.ArcadeDrive(vitesse, 0, false);
	deltaTime = timer.Get() - oldTime;
	cout << deltaTime << endl;
	oldTime = timer.Get();
	countdown -= deltaTime;
	cout << countdown << endl;
	if(countdown < 0) {
		if(vitesse != 0){
			oldVitesse = vitesse;
			vitesse = 0;
			countdown = 1;
			Drive.ArcadeDrive(0, 1, false);	
		}
		else { 
			if(oldVitesse < 0){
				vitesse = 0.2;
				countdown = 2;
			}
			else {
				vitesse = -0.2;
				countdown = 2;
			}
		}

	}


	} else {
		// Default Auto goes here
	}
}

void Robot::TeleopInit() {
	oldTime = timer.Get();
	soleCharge = 0;
	soleCooldown = 0;
}

void Robot::TeleopPeriodic() {
	// Utilise l'objet "Drive" pour effectuer un TankDrive, avec comme inputs les Y de 2 joysticks

	Drive.ArcadeDrive(joystick0.GetY(), joystick0.GetX(), true);

	// Temps écoulé entre deux itérations du téléop
	deltaTime = timer.Get()-oldTime;
	// Temps minimum à attendre avant de relancer la pneumatique
	soleCooldown -=deltaTime;

	// Incrémentation de la charge de la pneumatique
	if(joystick0.GetTop() && soleCharge < 2.55 && soleCooldown <= 0){
		soleCharge = (soleCharge+deltaTime<2.55)?soleCharge+deltaTime:2.55;
	}

	// Déclenchement du piston
	if(joystick0.GetTopReleased() && soleCooldown <= 0 && soleCharge >= 0.2)
	{
		sole.SetPulseDuration(soleCharge);
		sole.StartPulse();
		soleCooldown = soleCharge+2;
		soleCharge = 0;
	}

	// Permet d'utiliser deltaTime
	oldTime = timer.Get();
}

void Robot::TestPeriodic() {}

START_ROBOT_CLASS(Robot)
