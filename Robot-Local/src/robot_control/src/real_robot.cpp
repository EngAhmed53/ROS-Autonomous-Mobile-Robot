#include "real_robot.h"

RealRobot::Wheel::Wheel(const std::string &wheel_name, int counts_per_rev)
{
    name = wheel_name;
    rads_per_count = (2 * M_PI) / counts_per_rev;
}

double RealRobot::Wheel::calcEncAngle()
{
    return enc * rads_per_count;
}

RealRobot::RealRobot(const Config &cfg) : l_wheel_(cfg.left_wheel_name, cfg.enc_counts_per_rev),
                                          r_wheel_(cfg.right_wheel_name, cfg.enc_counts_per_rev)
{
    if (arduino_.connected())
    {
        arduino_.disconnect();
        ros::Duration(0.25).sleep();
    }

    arduino_.connect(cfg.device, cfg.baud_rate, cfg.timeout);

    //ros::Duration(1).sleep();

    //arduino_.set_pid_values(60, 0, 5, 0);

    loop_rate_ = cfg.loop_rate;

    // connect and register the joint state interface
    hardware_interface::JointStateHandle state_handle_a(l_wheel_.name, &l_wheel_.pos, &l_wheel_.vel, &l_wheel_.eff);
    jnt_state_interface_.registerHandle(state_handle_a);

    hardware_interface::JointStateHandle state_handle_b(r_wheel_.name, &r_wheel_.pos, &r_wheel_.vel, &r_wheel_.eff);
    jnt_state_interface_.registerHandle(state_handle_b);

    registerInterface(&jnt_state_interface_);

    // connect and register the joint position interface
    hardware_interface::JointHandle vel_handle_a(jnt_state_interface_.getHandle(l_wheel_.name), &l_wheel_.cmd);
    jnt_vel_interface_.registerHandle(vel_handle_a);

    hardware_interface::JointHandle vel_handle_b(jnt_state_interface_.getHandle(r_wheel_.name), &r_wheel_.cmd);
    jnt_vel_interface_.registerHandle(vel_handle_b);

    registerInterface(&jnt_vel_interface_);
}

void RealRobot::read()
{
    ros::Time new_time = ros::Time::now();
    period_ = new_time - time_;
    time_ = new_time;

    if (!arduino_.connected())
    {
        return;
    }

    arduino_.read_encoder_values(l_wheel_.enc, r_wheel_.enc);

    double pos_prev = l_wheel_.pos;
    l_wheel_.pos = l_wheel_.calcEncAngle();
    l_wheel_.vel = (l_wheel_.pos - pos_prev) / period_.toSec();

    pos_prev = r_wheel_.pos;
    r_wheel_.pos = r_wheel_.calcEncAngle();
    r_wheel_.vel = (r_wheel_.pos - pos_prev) / period_.toSec();
}

void RealRobot::write()
{
  if (!arduino_.connected())
  {
    return;
  }

  arduino_.set_motor_values(l_wheel_.cmd / l_wheel_.rads_per_count / loop_rate_, r_wheel_.cmd / r_wheel_.rads_per_count / loop_rate_);  // convert wheel velocity from (rad/seconds) to (encoder_counts/arduino PID loop rate)
}