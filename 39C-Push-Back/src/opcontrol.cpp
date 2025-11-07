#include "main.h"
#include "pros/motors.h"

void Control::opinit() {
    //controller
    controller.clear();
    leftDrive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightDrive.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

double Control::drive_control_map(double input) {
    if (abs(input) < 16) {
        return 0.0;
    }
    double ans;
    if (input > 0) {
        ans = (input - 16) / 111.0;
    }
    else {
        ans = (input + 16) / 111.0;
    }
    return ans;
}

double Control::boundBy(double l, double r, double value) {
    value = fmax(l, value);
    value = fmin(r, value);
    return value;
}

void Control::tankDrive(){
    double left = Control::drive_control_map(controller.get_analog(ANALOG_LEFT_Y));
    double right = Control::drive_control_map(controller.get_analog(ANALOG_RIGHT_Y));
    /*
    if(left==0){
        DriveTrain::stopLeft();
    }
    if(right==0){
        DriveTrain::stopRight();
    }
    */
    leftDrive.move_velocity(left*600);
    rightDrive.move_velocity(right*600);
}

void Control::tankLemlibDrive(){
    // get left y and right y positions. For this control, drive speed does not scale linearly with joystick position (there is a control function)
    int leftY = controller.get_analog(ANALOG_LEFT_Y);
    int rightY = controller.get_analog(ANALOG_RIGHT_Y);

    chassis.tank(leftY, rightY);
    pros::delay(25);
}

void Control::arcadeDrive(){
    double forward = Control::drive_control_map(controller.get_analog(ANALOG_LEFT_Y));
    double turn = Control::drive_control_map(controller.get_analog(ANALOG_RIGHT_X));
    double left=forward*500+turn*(300+forward*100);
    double right=forward*500-turn*(300+forward*100);
    if(left>600){
        int df=left-600;
        left=600;
        right-=df;
    }
    if(left<-600){
        int df=left+600;
        left=-600;
        right-=df;
    }
    if(right>600){
        int df=right-600;
        right=600;
        left-=df;
    }
    if(right<-600){
        int df=right+600;
        right=-600;
        left-=df;
    }
    leftDrive.move_velocity(Control::boundBy(-600,600,left));
    rightDrive.move_velocity(Control::boundBy(-600,600,right));
    /*
    if(turn==0&&forward==0){
        DriveTrain::stopLeft();
        DriveTrain::stopRight();
    }
    */
}

void Control::directionarcadeDrive(int direction) {

    double forward = direction * Control::drive_control_map(controller.get_analog(ANALOG_LEFT_Y));
    double turn = Control::drive_control_map(controller.get_analog(ANALOG_RIGHT_X));
    double left=forward*500+turn*(300+forward*100);
    double right=forward*500-turn*(300+forward*100);
    if(left>600){
        int df=left-600;
        left=600;
        right-=df;
    }
    if(left<-600){
        int df=left+600;
        left=-600;
        right-=df;
    }
    if(right>600){
        int df=right-600;
        right=600;
        left-=df;
    }
    if(right<-600){
        int df=right+600;
        right=-600;
        left-=df;
    }
    leftDrive.move_velocity(Control::boundBy(-600,600,left));
    rightDrive.move_velocity(Control::boundBy(-600,600,right));
    /*
    if(turn==0&&forward==0){
        DriveTrain::stopLeft();
        DriveTrain::stopRight();
    }
    */
}

/*
intake to low -> 1 + 2 + 3 + 6 - (4 5 X)
intake to high (Default)-> 1 + 2 - 3 - 6 + (4 5 X)

Conveying -> 1 + 2 - 3- 6 + -> Same with intake to high

Outtake mid -> 3 + 5 -
Outtake high -> 3 - 4 - 5 +
Outtake low -> 1 - 2 - 3 - 6 + 

** 체크해야 할 상황 => convey 돌리다가 low로 배출 가능할지 **
*/

void Control::controls(){

    //intake
    /*
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1 )) {          //intake to low
        intake1.move_voltage(12000);
        intake2.move_voltage(12000);
        conveyer3.move_voltage(12000);
        intake6.move_voltage(-12000);
    } else
    */
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {      // intake to high
        intake1.move_voltage(12000);
        intake2.move_voltage(-12000);
        conveyer3.move_voltage(-12000);
        intake6.move_voltage(12000);
    } else {
        intake1.move_voltage(0);
        intake2.move_voltage(0);
        conveyer3.move_voltage(0);
        intake6.move_voltage(0);
    }

    //outtake
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {           // outtake to low
        intake1.move_voltage(-12000);
        intake2.move_voltage(-12000);
        conveyer3.move_voltage(-12000);
        intake6.move_voltage(12000);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {    // outtake to high
        conveyer3.move_voltage(-12000);
        outtake4.move_voltage(-12000);
        outtake5.move_voltage(12000);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {    //outtake to mid
        conveyer3.move_voltage(12000);
        outtake5.move_voltage(-12000);
    } else {
        outtake4.move_voltage(0);
        outtake5.move_voltage(0);
    }

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        move = -1 * move;
    }

}

void Control::debug(){
    pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
    pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
    pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
}

void Control::opupdate(){
    Control::directionarcadeDrive(move);
    Control::controls();
}