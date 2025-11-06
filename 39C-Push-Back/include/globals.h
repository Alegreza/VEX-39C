#pragma once
#include "lemlib/chassis/chassis.hpp"
#include "main.h"


extern pros::Controller controller;
extern pros::MotorGroup leftDrive;
extern pros::MotorGroup rightDrive;

extern pros::Motor intake1;
extern pros::Motor intake2;
extern pros::Motor conveyer3;
extern pros::Motor outtake4;
extern pros::Motor outtake5;
extern pros::Motor intake6;

extern pros::Rotation odom;
extern pros::Imu inertial;

extern lemlib::Chassis chassis;

extern pros::Optical optical;

extern bool teamRed;
extern bool scoringLow;