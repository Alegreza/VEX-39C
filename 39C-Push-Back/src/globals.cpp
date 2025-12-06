#include "globals.h"
#include "main.h"
#include "pros/abstract_motor.hpp"

const int UNDEF = 50;
//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//drivetrain
pros::MotorGroup left_motor_group({-1, -2}, pros::MotorGears::blue);
pros::MotorGroup right_motor_group({17, 18}, pros::MotorGears::blue);

//Intake/Outtake motors
pros::Motor intake1(19, pros::v5::MotorGears::green);
pros::Motor intake2(20, pros::v5::MotorGears::green);
pros::Motor conveyer3(8, pros::v5::MotorGears::blue);
pros::Motor outtake4(4, pros::v5::MotorGears::green);
pros::Motor outtake5(3, pros::v5::MotorGears::green);
pros::Motor intake6(11, pros::v5::MotorGears::green);
pros::Motor flap7(10, pros::v5::MotorGears::green);

pros::Imu inertial(12);

pros::Rotation verticalEnc(-7);
pros::Rotation horizontalEnc(-5);

pros::ADIDigitalOut matchload('D',false);



lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_2, 8.5);
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_2, 0.5);

//global vars
bool teamRed = true;
int move = 1;

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
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
                            &inertial // in ertial sensor
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