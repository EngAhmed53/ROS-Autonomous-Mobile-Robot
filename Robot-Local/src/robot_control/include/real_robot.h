#ifndef REAL_ROBOT_H
#define REAL_ROBOT_H

#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include <libserial/SerialPort.h>
#include "arduino_comms.h"
#include <cstring>

class RealRobot : public hardware_interface::RobotHW
{

public:
    struct Config
    {
        std::string left_wheel_name = "left_wheel_joint", right_wheel_name = "right_wheel_joint";
        float loop_rate = 30;
        std::string device = "/dev/ttyACM0";
        int baud_rate = 57600;
        int timeout = 1000;
        int enc_counts_per_rev = 225;
    };

private:
    struct Wheel
    {
        std::string name = "";
        long enc = 0;
        double cmd = 0;
        double pos = 0;
        double vel = 0;
        double eff = 0;
        double rads_per_count = 0;

        Wheel(const std::string &wheel_name, int counts_per_rev);

        double calcEncAngle();
    };

public:
    RealRobot(const Config &config);
    void read();
    void write();

    ros::Time get_time() const { return time_; }
    ros::Duration get_period() const { return period_; }

private:
    hardware_interface::JointStateInterface jnt_state_interface_;
    hardware_interface::VelocityJointInterface jnt_vel_interface_;
    ArduinoComms arduino_;

    Wheel l_wheel_;
    Wheel r_wheel_;

    ros::Time time_;
    ros::Duration period_;
    float loop_rate_;
};
#endif