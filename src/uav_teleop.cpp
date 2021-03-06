/**
 * @file uav_teleop.h
 * @author Seungwook Lee (seungwook1024@gmail.com), USRG@KAIST
 * @brief UAVTeleop class implementation.
 * @version 0.1
 * @date 2022-05-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "uav_teleop/uav_teleop.h"

UAVTeleop::UAVTeleop() : Node("uav_teleop")
{
    RCLCPP_INFO(get_logger(), "Creating");

    initParameters();

    joy_input_ = std::make_shared<JoyInput>();

    joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
        "joy", rclcpp::QoS(1), std::bind(&UAVTeleop::joy_sub_callback, this, _1));
    command_pub_ = this->create_publisher<geometry_msgs::msg::Twist>(
        "cmd_vel", rclcpp::QoS(1));

    timer_ = this->create_wall_timer(
            std::chrono::milliseconds((int)(1.0/rate_*1000)),
            std::bind(&UAVTeleop::timerCallback, this));
}

UAVTeleop::~UAVTeleop()
{
}

void UAVTeleop::initParameters()
{
    // @TODO: Identify needed parameters.
    uav_name_ = this->get_namespace();
    declare_parameter("rate", 20.0);
    get_parameter("rate", rate_); // hz
    declare_parameter("max_speed", 1.0);
    get_parameter("max_speed", max_speed_);
    declare_parameter("max_yaw_speed", 1.0);
    get_parameter("max_yaw_speed", max_yaw_speed_);

    // Print out for debugging.
    RCLCPP_INFO(get_logger(), "Parameter List");
    RCLCPP_INFO(get_logger(), "uav_name: %s", uav_name_.c_str());
    RCLCPP_INFO(get_logger(), "max_speed: %f", max_speed_);
    RCLCPP_INFO(get_logger(), "max_yaw_speed: %f", max_yaw_speed_);
    
}

void UAVTeleop::joy_sub_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
{
    get_parameter("max_speed", max_speed_);
    get_parameter("max_yaw_speed", max_yaw_speed_);

    joy_input_->roll     = msg->axes[3] * (-1); // RHS axis left <-> right
    joy_input_->pitch    = msg->axes[4];        // RHS axis   up <-> down
    joy_input_->yaw      = msg->axes[0];        // LHS axis left <-> right 
    joy_input_->throttle = msg->axes[1];        // LHS axis   up <-> down

    // TODO reserved
    joy_input_->arm      = msg->buttons[0];     // logitech A           button | ps joy X               button
    joy_input_->takeoff  = msg->axes[7];        // logitech arrow up    button | ps joy arrow up = 1    button
    joy_input_->land     = msg->axes[7] * (-1); // logitech arrow down  button | ps joy arrow down = 1  button
    joy_input_->mode     = msg->buttons[5];     // logitech LB          button | ps joy R1              button

}

void UAVTeleop::timerCallback()
{
    publishCommand(joy_input_);
}

void UAVTeleop::publishCommand(const std::shared_ptr<JoyInput> joy_input)
{
    get_parameter("max_speed", max_speed_);
    get_parameter("max_yaw_speed", max_yaw_speed_);

    geometry_msgs::msg::Twist cmd_vel;
    double klin = max_speed_;
    double kang = max_yaw_speed_;
    cmd_vel.linear.x  = klin * joy_input->pitch;
    cmd_vel.linear.y  = klin * joy_input->roll * (-1);
    cmd_vel.linear.z  = klin * joy_input->throttle;
    cmd_vel.angular.z = kang * joy_input->yaw;

    command_pub_->publish(cmd_vel);
}
