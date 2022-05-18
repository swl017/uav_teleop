#include "uav_teleop/uav_teleop.h"


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<UAVTeleop>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;

}
