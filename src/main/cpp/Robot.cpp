/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include "version.h"
#include "ctre/Phoenix.h"
#include <frc/Joystick.h>

using namespace frc;

Version *print;
TalonSRX *talon_drive_left_noenc, *talon_drive_left_enc, *talon_drive_right_enc, *talon_drive_right_noenc;
Timer *timer;

std::string storage = "";
std::string storage_header = "";

std::string filename = "Auto";

int num_talon_drive_left_noenc = 1;
int num_talon_drive_right_noenc = 4;
int num_talon_drive_left_enc = 2;
int num_talon_drive_right_enc = 3;

void Robot::RobotInit() {
	talon_drive_left_noenc = new TalonSRX(num_talon_drive_left_noenc);
	talon_drive_left_enc = new TalonSRX(num_talon_drive_left_enc);
	talon_drive_right_noenc = new TalonSRX(num_talon_drive_right_noenc);
	talon_drive_right_enc = new TalonSRX(num_talon_drive_right_enc);

	talon_drive_right_noenc->Set(ControlMode::Follower, num_talon_drive_right_enc);
	talon_drive_left_noenc->Set(ControlMode::Follower, num_talon_drive_left_enc);

	timer = new Timer();

	print = new Version(filename);
	std::cout<<filename<<" V"<<print->SaveVersionNumber()<<std::endl;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
	timer->Start();
}

void Robot::TeleopPeriodic() {
	print->AddToPipeDelimitedFile("Time", print->ToString(timer->Get()), storage_header, storage, false);
	print->AddToPipeDelimitedFile("Battery Voltage", print->ToString(DriverStation::GetInstance().GetBatteryVoltage()), storage_header, storage, false);
	
	TalonEncPrintOuts(talon_drive_left_enc, "Talon Left Drive Encoder");
	TalonEncPrintOuts(talon_drive_right_enc, "Talon Right Drive Encoder");
	TalonNoEncPrintOuts(talon_drive_left_noenc, "Talon Left Drive No Encoder");
	TalonNoEncPrintOuts(talon_drive_right_noenc, "Talon Right Drive No Encoder");

	print->EndLoop(storage);
}

void Robot::TalonEncPrintOuts(TalonSRX *talon_enc, std::string talon_name){
	print->AddToPipeDelimitedFile(std::string(talon_name + " Position"), print->ToString(talon_enc->GetSelectedSensorPosition(0)), storage_header, storage, false);
	print->AddToPipeDelimitedFile(std::string(talon_name + " Velocity"), print->ToString(talon_enc->GetSelectedSensorVelocity(0)), storage_header, storage, false);
	print->AddToPipeDelimitedFile(std::string(talon_name + " Amperage"), print->ToString(talon_enc->GetOutputCurrent()), storage_header, storage, false);
}

void Robot::TalonNoEncPrintOuts(TalonSRX *talon_enc, std::string talon_name){
	print->AddToPipeDelimitedFile(std::string(talon_name + " Amperage"), print->ToString(talon_enc->GetOutputCurrent()), storage_header, storage, false);
}

void Robot::TestPeriodic() {}

void Robot::DisabledInit(){
	if (storage.find(std::string("|")) != std::string::npos) print->CreateSaveFile(storage_header + "\n" + storage);
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif