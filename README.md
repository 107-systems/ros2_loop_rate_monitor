<a href="https://107-systems.org/"><img align="right" src="https://raw.githubusercontent.com/107-systems/.github/main/logo/107-systems.png" width="15%"></a>
:floppy_disk: `ros2_loop_rate_monitor`
======================================
[![Build Status](https://github.com/107-systems/ros2_loop_rate_monitor/actions/workflows/ros2.yml/badge.svg)](https://github.com/107-systems/ros2_loop_rate_monitor/actions/workflows/ros2.yml)
[![Spell Check status](https://github.com/107-systems/ros2_loop_rate_monitor/actions/workflows/spell-check.yml/badge.svg)](https://github.com/107-systems/ros2_loop_rate_monitor/actions/workflows/spell-check.yml)

This library provides functionality for monitoring the loop rate of your timed ROS loop.

<p align="center">
  <a href="https://github.com/107-systems/l3xz"><img src="https://raw.githubusercontent.com/107-systems/.github/main/logo/l3xz-logo-memento-mori-github.png" width="40%"></a>
</p>

#### How-to-build
```bash
cd $COLCON_WS/src
git clone https://github.com/107-systems/ros2_loop_rate_monitor
cd $COLCON_WS
source /opt/ros/humble/setup.bash
colcon build --packages-select ros2_loop_rate_monitor
```

#### How-to-use
* **package.xml**:
```diff
+   <depend>ros2_loop_rate_monitor</depend>
```
* **CMakeLists.txt**:
```diff
+   find_package(ros2_loop_rate_monitor REQUIRED)
...
-   ament_target_dependencies(${MY_TARGET} rclcpp)
+   ament_target_dependencies(${MY_TARGET} rclcpp ros2_loop_rate_monitor)
```
* **Node.h/.cpp**:
```C++
#include <ros2_loop_rate_monitor/Monitor.h>
/* ... */
static std::chrono::milliseconds constexpr IO_LOOP_RATE{10};
loop_rate::Monitor::SharedPtr _io_loop_rate_monitor;
/* ... */
_io_loop_rate_monitor = loop_rate::Monitor::create(IO_LOOP_RATE, std::chrono::milliseconds(1));
/* ... */
void Node::io_loop()
{
  _io_loop_rate_monitor->update();
  if (auto const [timeout, opt_timeout_duration] = _io_loop_rate_monitor->isTimeout();
    timeout == loop_rate::Monitor::Timeout::Yes)
  {
    RCLCPP_WARN_THROTTLE(get_logger(),
                         *get_clock(),
                         1000,
                         "io_loop should be called every %ld ms, but is %ld ms instead",
                         IO_LOOP_RATE.count(),
                         opt_timeout_duration.value().count());
  }
  /* ... */
```
