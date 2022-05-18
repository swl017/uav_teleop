#include "uav_teleop/uav_teleop.h"

UAVTeleop::UAVTeleop() : Node("uav_teleop")
{
    RCLCPP_INFO(get_logger(), "Creating");

    initParameters();

    joy_input_ = std::make_shared<JoyInput>();

    joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
        "joy", rclcpp::QoS(1), std::bind(&UAVTeleop::joy_sub_callback, this, _1));
    // control_pub_ = this->create_publisher<ackermann_msgs::msg::AckermannDriveStamped>(
    //     "mpc/control", rclcpp::QoS(1));

    // this->declare_parameter<bool>("use_mpc_planner", false);
    // this->declare_parameter<bool>("use_game", false);
    // this->get_parameter("use_mpc_planner", use_mpc_planner_);
    // this->get_parameter("use_game", use_game_);

}

UAVTeleop::~UAVTeleop()
{
}

void UAVTeleop::initParameters()
{
    // @TODO: Identify needed parameters.
    declare_parameter("alpha1", 0.2);
    get_parameter("alpha1", alpha1_);
}

void UAVTeleop::joy_sub_callback(const sensor_msgs::msg::Joy::SharedPtr msg) const
{
    // @TODO: Match axes index to rpy.
    joy_input_->roll     = msg->axes[0];
    joy_input_->pitch    = msg->axes[0];
    joy_input_->yaw      = msg->axes[0];
    joy_input_->throttle = msg->axes[0];
    joy_input_->arm      = msg->axes[0];
    joy_input_->takeoff  = msg->axes[0];
    joy_input_->land     = msg->axes[0];

    // @TODO: Added the publisher here.
}
