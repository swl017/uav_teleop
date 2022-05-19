/**
 * @file uav_teleop.h
 * @author Seungwook Lee (seungwook1024@gmail.com), USRG@KAIST
 * @brief Header file for UAVTeleop class implementation.
 * @version 0.1
 * @date 2022-05-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef UAV_TELEOP_H
#define UAV_TELEOP_H

#include <memory>
#include <math.h>


#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "geometry_msgs/msg/twist.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class UAVTeleop : public rclcpp::Node
{
public:
    UAVTeleop();
    ~UAVTeleop();

    struct JoyInput
    {
        JoyInput(){};
        double roll;
        double pitch;
        double yaw;
        double throttle;
        int arm;
        int takeoff;
        int land;
        int mode;
    };

protected:
    void initParameters();

    void joy_sub_callback(const sensor_msgs::msg::Joy::SharedPtr msg);
    void publishCommand(const std::shared_ptr<JoyInput> joy_input);
    void timerCallback();

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr command_pub_;
    // rclcpp::Service<vrxperience_custom_msg::srv::HighLvlService>::SharedPtr high_level_control_service_;

private:
    rclcpp::TimerBase::SharedPtr timer_;

    std::string uav_name_;
    double rate_; // hz
    double max_speed_;
    double max_yaw_speed_;
    std::shared_ptr<JoyInput> joy_input_;


};

#endif // UAV_TELEOP_H