/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <rev/CANSparkMax.h>
#include "UDPClient.h"
#include <frc/RobotDrive.h>
#include <frc/TimedRobot.h>
#include "SFDrive_SparkMax.h"
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/DriverStation.h>


class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void DisabledInit() override;

 private:

  const int rMotorFrontNum = 13;
  const int rMotorBackNum = 16;
  const int lMotorFrontNum = 2;
  const int lMotorBackNum = 3;
  const int driveMotorCurrentLimit = 40;
  const int ticksPerRev = 42;
  const double wheelCircumference = 6 * 3.14159;
  const double pConstantDrive = 4;
  const double iConstantDrive = 0;
  const double dConstantDrive = 0;
  const double fConstantDrive = 0;
  const int maxAccel = 8000;


  UDPClient * metrics =   metrics = new UDPClient;

  rev::CANSparkMax * lMotorFront = new rev::CANSparkMax(lMotorFrontNum, rev::CANSparkMax::MotorType::kBrushless);
  rev::CANSparkMax * lMotorBack = new rev::CANSparkMax(lMotorBackNum, rev::CANSparkMax::MotorType::kBrushless);
  rev::CANSparkMax * rMotorBack = new rev::CANSparkMax(rMotorBackNum, rev::CANSparkMax::MotorType::kBrushless);
  rev::CANSparkMax * rMotorFront = new rev::CANSparkMax(rMotorFrontNum, rev::CANSparkMax::MotorType::kBrushless);

  SFDrive_SparkMax * robot = new SFDrive_SparkMax(lMotorFront, rMotorFront, pConstantDrive, iConstantDrive, dConstantDrive, fConstantDrive);


};
