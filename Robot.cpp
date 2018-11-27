
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

		timer.Start();
		cout << deltaTime << endl;
		countdown = 2;
		vitesse = 0.1;
		vitesse_x = 0.3;
		etapes = 1;

	} else {

		// Default Auto goes here
	}



}

void Robot::AutonomousPeriodic() {

	if (m_autoSelected == kAutoNameCustom) {

		// Custom Auto goes here

	cout << "J'avance!" << endl;
	deltaTime = timer.Get() - oldTime;
	cout << deltaTime << endl;
	oldTime = timer.Get();
	countdown -= deltaTime;
	cout << countdown << endl;



	if(countdown <= 0) {

		switch(etapes) {

			case 1:
				Drive.ArcadeDrive(vitesse, 0, true);
				etapes++;
				countdown = 2;
				break;
			case 2:
				Drive.ArcadeDrive(0, vitesse_x, true);
				etapes++;
				countdown = 2;
				break;
			case 3:
				Drive.ArcadeDrive(vitesse, 0, true);
				etapes++;
				countdown = 2;
				break;
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



	// Permet d'utiliser deltaTime

	oldTime = timer.Get();

}



void Robot::TestPeriodic() {}



START_ROBOT_CLASS(Robot)
