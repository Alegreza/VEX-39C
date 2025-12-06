#pragma once
#include "main.h"

class Autonomous{
    public:
        static void init();
        static void tuneAngularPID();
        static void tuneLateralPID();
        static void constantlyPrintPose();
        static void skillsAuton();
        static void intake();
        static void outtaketomid();
};
