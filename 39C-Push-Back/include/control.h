#pragma once
#include "main.h"

class Control{
    public:
        static void opupdate();
        static void opinit();
        static void debug();
    private:
        static double drive_control_map(double input);
        static double boundBy(double l, double r, double value);
        static void controls();
        static void tankLemlibDrive();
        static void tankDrive();
        static void arcadeDrive();
};