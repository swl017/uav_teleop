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
> Takeoff by pushing the throttle(left axes stick) up, move around using roll, pitch(right axes)


## The Joystick
- Model: Dualshock 4
- Controller mode: Mode 2(Default), Mode 1(TODO)
