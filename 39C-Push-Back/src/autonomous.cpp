#include "autonomous.h"
#include "globals.h"
#include "main.h"
#include "pros/llemu.hpp"

auto &outbput = std::cout;

void Autonomous::constantlyPrintPose() {
    while (true) {
        pros::lcd::print(0, "x: %f", chassis.getPose().x);
        pros::lcd::print(1, "Y: %f", chassis.getPose().y);
        pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
        pros::delay(50);
    }
}

void Autonomous::init() {
    // inertial.reset(true);
    // inertial.tare();
    // while (inertial.is_calibrating()) {
    //     pros::delay(10);
    //     pros::lcd::print(0, "calibrating");
    // }
    // chassis.calibrate();
    // chassis.setPose({0,0,0});
    // // optical.set_led_pwm(100); <--optical sensor (will be put in later)
    // pros::Task printPoseTask(Autonomous::constantlyPrintPose);  //multithreading: constantly print position, seperate from main code.*/
} 

void Autonomous::intake() {
    intake1.move_voltage(12000);
    intake2.move_voltage(-12000);
    conveyer3.move_voltage(-12000);
    intake6.move_voltage(12000);
}

void Autonomous::outtaketomid() {
    intake1.move_voltage(12000);
    intake2.move_voltage(12000);
    conveyer3.move_voltage(12000);
    outtake5.move_voltage(-12000);
    intake6.move_voltage(-12000);
}



void Autonomous::tuneAngularPID() {
    chassis.setPose({0,0,0});
    chassis.turnToHeading(90, 2000, {}, false); // 90도에서만 이상하게 돌고 또 360에서는 왜 정상으로 뜸????
    pros::delay(1000);
    chassis.turnToHeading(180,2000,{},false);
    pros::delay(1000);
    chassis.turnToHeading(270, 2000,{},false);
    pros::delay(1000);
    chassis.turnToHeading(360,2000,{},false);
}

void Autonomous::tuneLateralPID() {
    chassis.setPose({0,0,0});
    chassis.moveToPoint(0,30, 20000, {}, false);
    chassis.moveToPoint(0, 0, 20000, {.forwards = false}, false);
}

void Autonomous::skillsAuton() {
    Autonomous::intake();
    //chassis
    chassis.moveToPoint(0,10, 4000, {.forwards = false});
    matchload.set_value(false);
    chassis.moveToPoint(0, 10, 4000);
    //chassis.moveToPoint(7,35,4000);
    //chassis.turnToHeading(45, 4000);
}