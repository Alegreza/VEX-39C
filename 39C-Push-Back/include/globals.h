#pragma once
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.hpp"


extern pros::Controller controller;
extern pros::MotorGroup leftDrive;
extern pros::MotorGroup rightDrive;

extern pros::Motor intake1;
extern pros::Motor intake2;
extern pros::Motor conveyer3;
extern pros::Motor outtake4;
extern pros::Motor outtake5;
extern pros::Motor intake6;

extern pros::ADIDigitalOut matchload;

extern pros::Rotation verticalEnc;
extern pros::Rotation horizontalEnc;

extern pros::Rotation odom;
extern pros::Imu inertial;

extern lemlib::Chassis chassis;

extern pros::Optical optical;

extern bool teamRed;
extern int move; //give +1 or -1, so that they can change the direction 
