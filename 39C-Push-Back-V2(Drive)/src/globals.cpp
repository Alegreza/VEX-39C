#include "globals.h"
#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"

const int UNDEF = 50;
//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//drivetrain
pros::MotorGroup leftDrive({-19, -7, 12}, pros::MotorGears::blue);
pros::MotorGroup rightDrive({11, -18, 3}, pros::MotorGears::blue);

//Intake/Outtake motors
pros::Motor intake(10 , pros::v5::MotorGears::green);
pros::Motor middle(8,pros::v5::MotorGears::green);
pros::Motor outtakelow(4, pros::v5::MotorGears::green);
pros::Motor outtakehigh(9, pros::v5::MotorGears::green);

pros::Imu inertial(0);

pros::Rotation verticalEnc(0);
pros::Rotation horizontalEnc(0);

pros::ADIDigitalOut Rmatchload('D',true);
pros::ADIDigitalOut Lmatchload('B', true);
pros::ADIDigitalOut topblock('A', true);
pros::ADIDigitalOut descore('C', true);

lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, 8.5);
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, 0.5);

//global vars
bool teamRed = true;
int move = 1;
bool topblockvalue = true;
bool descorevalue = true;

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftDrive, // left motor group
                              &rightDrive, // right motor group
                              12.5, // 12.5 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              360, // drivetrain rpm is 360 since the gear ratio is 1:0.6
                              2 // horizontal drift is 2 (for now) <--need to be changed
);

lemlib::ControllerSettings angular_controller(3, // proportional gain (kP)
                                              0.0001, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0.0001, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// odometry settings
lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial // inertial sensor
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                 10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

lemlib::Chassis chassis(drivetrain,
                        lateral_controller, 
                        angular_controller, 
                        sensors, 
                        &throttle_curve, 
                        &steer_curve
);