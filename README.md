# uav_teleop

## Dependencies
`rosdep` single-line dependency installation.
```bash
rosdep install --from-paths . --ignore-src -r -y
```

> Alternatively,
> ```bash
> sudo apt install ros-galactic-mavros ros-galactic-joy
> ```

## Usage
```bash
ros2 run uav_teleop uav_teleop_node --ros-args -r __ns:=/uav2 -p max_speed:=2.0 
```
> Reference: http://docs.ros.org/en/ros2_documentation/galactic/How-To-Guides/Node-arguments.html