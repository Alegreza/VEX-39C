#include "main.h"
#include "pros/motors.h"

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

/*
intake to low -> 1 + 2 + 3 + 6 - (4 5 X)
intake to high (Default)-> 1 + 2 - 3 - 6 + (4 5 X)

Conveying -> 1 + 2 - 3- 6 + -> Same with intake to high

Outtake mid -> 3 + 5 -
Outtake high -> 3 - 4 - 5 +
Outtake low -> 1 - 2 - 3 - 6 + 

** 체크해야 할 상황 => convey 돌리다가 low로 배출 가능할지
*/

void Control::controls(){

    //intake
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1 )) {          //intake to low
        intake1.move_voltage(12000);
        intake2.move_voltage(12000);
        conveyer3.move_voltage(12000);
        intake6.move_voltage(-12000);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {      // intake to high
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
    if ((controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))&&(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))) {           // outtake to low
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
    } 


}

void Control::debug(){
    pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
    pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
    pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
}

void Control::opupdate(){
    Control::tankLemlibDrive();
    Control::controls();
}