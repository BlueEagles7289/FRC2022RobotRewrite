// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>



void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but befor`e
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
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {

  #pragma region Variables

    double tempLoader = 0;
    double tempMagazine = 0;
    double tempShooter = 0;
    double tempLiftArm = 0;
    double tempRotateArm = 0;

    double tempX = controllerDriver.GetX();
    double tempY = controllerDriver.GetY();
    double tempRot = controllerDriver.GetTwist();
    
    bool tempButtonUp = controlBoard.GetRawButton(1);
    bool tempButtonLeft = controlBoard.GetRawButton(2);
    bool tempButtonDown = controlBoard.GetRawButton(3);
    bool tempButtonRight = controlBoard.GetRawButton(4);
    bool tempButtonLoad = controlBoard.GetRawButton(5);
    bool tempButtonLiftMode = controlBoard.GetRawButton(6);
    bool tempButtonShoot = controlBoard.GetRawButton(7);
    bool tempButtonShooter = controlBoard.GetRawButton(8);
    bool tempButtonMagazine = controlBoard.GetRawButton(10);
    bool tempButtonOverride = controlBoard.GetRawButton(12);

    bool tempPELoader = PELoader.Get();
    bool tempPEMagazine = PEMagazine.Get();

  #pragma endregion



  #pragma region Set Robot Mode

    if(tempButtonLiftMode){
      robotMode = enumRobotMode::lift;
    } else {
      robotMode = enumRobotMode::drive;
    }

  #pragma endregion



  if(robotMode == enumRobotMode::drive){

    if(tempButtonLoad){
      
      //PE is clear
      if(tempPELoader || tempPEMagazine){
        
        tempLoader = 0.2;

      }

    }
    
    if(tempButtonMagazine){
      
      //PE is clear
      if(tempPEMagazine){

        tempMagazine = 0.05;

      }

      if(tempButtonShooter){
        
        tempMagazine = 0.6;

      }

    }
    
    if(tempButtonShoot){
      
      tempShooter = 0.6;

    }
      

  } else if(robotMode == enumRobotMode::lift) {
    
    if(tempButtonUp && !LiftUpperLimit.Get()){
      m_Lift.Set(1);
    } else if(tempButtonDown && !LiftLowerLimit.Get()){
      m_Lift.Set(-1);
    }


    if(tempX > 0 && !RotateArmFrontLimit.Get()){

      tempRotateArm = tempX * 0.5;

    } else if(tempX < 0 && !RotateArmBackLimit.Get()){

      tempRotateArm = tempX * 0.5;

    }

    //Set movement to 0 since we don't move in lift mode
    tempX = 0;
    tempY = 0;
    tempRot = 0;

  } else {

    ;//Shouldn't get here

  }

  m_RotateArm.Set(tempRotateArm);
  m_Magazine.Set(tempMagazine);
  m_Loader.Set(tempLoader);
  m_Shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput ,tempShooter);
  m_robotDrive.DriveCartesian(tempX * 0.5, tempY * 0.75, tempRot * 0.5);

}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
