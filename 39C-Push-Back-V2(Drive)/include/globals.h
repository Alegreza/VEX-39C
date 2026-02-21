#pragma once
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"


extern pros::Controller controller;
extern pros::MotorGroup leftDrive;
extern pros::MotorGroup rightDrive;

extern pros::Motor intake;
extern pros::Motor middle;
extern pros::Motor outtakehigh;
extern pros::Motor outtakelow;

extern pros::ADIDigitalOut topblock;
extern pros::ADIDigitalOut Rmatchload;
extern pros::ADIDigitalOut Lmatchload;
extern pros::ADIDigitalOut descore;

extern pros::Rotation verticalEnc;
extern pros::Rotation horizontalEnc;

extern pros::Rotation odom;
extern pros::Imu inertial;

extern lemlib::Chassis chassis;

extern pros::Optical optical;

extern bool teamRed;
extern int move; //give +1 or -1, so that they can change the direction 
extern bool topblockvalue;
extern bool descorevalue;
