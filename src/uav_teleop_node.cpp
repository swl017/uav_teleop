/**
 * @file uav_teleop.h
 * @author Seungwook Lee (seungwook1024@gmail.com), USRG@KAIST
 * @brief  UAVTeleop ros2 node implementation.
 * @version 0.1
 * @date 2022-05-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "uav_teleop/uav_teleop.h"


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<UAVTeleop>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;

}
