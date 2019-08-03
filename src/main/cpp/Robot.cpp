/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
 
   //Set current limit for drive motors
    rMotorFront->SetSmartCurrentLimit(driveMotorCurrentLimit);
    lMotorFront->SetSmartCurrentLimit(driveMotorCurrentLimit);
    rMotorBack->SetSmartCurrentLimit(driveMotorCurrentLimit);
    lMotorBack->SetSmartCurrentLimit(driveMotorCurrentLimit);
    metrics->setup_socket();

    //rMotorFront->SetInverted(true);
    rMotorBack->Follow(*rMotorFront, false);
   // lMotorFront->SetInverted(false);
    lMotorBack->Follow(*lMotorFront, false);

    double min = 0;
    double max = 10;

      frc::SmartDashboard::PutNumber("P: ", pConstantDrive);
      frc::SmartDashboard::PutNumber("I: ", iConstantDrive);
      frc::SmartDashboard::PutNumber("D: ", dConstantDrive);
       

      frc::SmartDashboard::PutNumber("Min output: ", min);
      frc::SmartDashboard::PutNumber("Max output: ",max );

     // lMotorFront->GetPIDController().SetOutputRange(min, max);
     // rMotorFront->GetPIDController().SetOutputRange(min, max);


    

    
    
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

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

  
 // metrics->UDPReadThread();
  
 // double angle = metrics->getAngle();
 // double distance = metrics->getDistance();

  robot->PIDTurnInPlace(360, maxAccel);
  frc::DriverStation::ReportError("in auton");



}

void Robot::AutonomousPeriodic() { 
         
  frc::DriverStation::ReportError("left: " + std::to_string(lMotorFront->GetEncoder().GetPosition()) + " right "+ std::to_string(rMotorFront->GetEncoder().GetPosition()));
  frc::SmartDashboard::PutNumber("left auton: ", lMotorFront->GetEncoder().GetPosition());
  frc::SmartDashboard::PutNumber("right auton: ", rMotorFront->GetEncoder().GetPosition());

}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::TestPeriodic() {


}

void Robot::DisabledInit(){
  
  metrics->stopUDPThread();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
