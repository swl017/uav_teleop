#ifndef UAV_TELEOP_H
#define UAV_TELEOP_H

#include <memory>
#include <math.h>


#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"


#include "std_msgs/msg/string.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include <std_msgs/msg/float64.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <std_msgs/msg/color_rgba.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

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
    };

protected:
    void initParameters();

    void joy_sub_callback(const sensor_msgs::msg::Joy::SharedPtr msg) const;

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
    // rclcpp::Publisher<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr control_pub_;
    // rclcpp::Service<vrxperience_custom_msg::srv::HighLvlService>::SharedPtr high_level_control_service_;

private:
    double alpha1_;
    std::shared_ptr<JoyInput> joy_input_;


};

#endif // UAV_TELEOP_H