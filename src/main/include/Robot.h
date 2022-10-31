// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/motorcontrol/PWMTalonSRX.h>
#include <frc/motorcontrol/PWMTalonFX.h>
//Controller
#include <frc/XboxController.h>
#include <frc/Joystick.h>

//Digital Inputs
#include <frc/DigitalInput.h>

//Pigeon
//#include <ctre/phoenix/sensors/PigeonIMU.h>
#include <ctre/Phoenix.h>

enum enumRobotMode{none, drive, lift};

class Robot : public frc::TimedRobot {
 public:

 int robotMode = enumRobotMode::none;

  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  #pragma region Motors

    frc::PWMTalonFX m_TalonSRXMotorFrontLeft{1};
    frc::PWMTalonFX m_TalonSRXMotorBackLeft{4};
    frc::PWMTalonFX m_TalonSRXMotorFrontRight{3};
    frc::PWMTalonFX m_TalonSRXMotorBackRight{2};

    frc::MecanumDrive m_robotDrive{m_TalonSRXMotorFrontLeft, m_TalonSRXMotorBackLeft, m_TalonSRXMotorFrontRight,
                                  m_TalonSRXMotorBackRight};

    frc::PWMTalonFX m_RotateArm{5};
    frc::PWMTalonSRX m_Lift{6};
    frc::PWMTalonSRX m_Loader{7};
    frc::PWMTalonSRX m_Magazine{8};
    //frc::PWMTalonSRX m_Shooter{9};

    TalonSRX m_Shooter{9};

  #pragma endregion

  frc::XboxController m_driverController{0};

  frc::Joystick controllerDriver{1};
  frc::Joystick controlBoard{2};

  frc::DigitalInput RotateArmBackLimit{4};
  frc::DigitalInput RotateArmFrontLimit{5};
  frc::DigitalInput LiftLowerLimit{0};
  frc::DigitalInput LiftUpperLimit{1};

  frc::DigitalInput PELoader{2};
  frc::DigitalInput PEMagazine{3};

  PigeonIMU s_pigeon{m_Shooter};

};
