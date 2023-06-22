#######################################################################################
cmake_minimum_required(VERSION 3.8)
#######################################################################################
project(ros2_loop_rate_monitor)
set(ROS2_LOOP_RATE_MONITOR_TARGET ${PROJECT_NAME})
#######################################################################################
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
#######################################################################################
find_package(ament_cmake REQUIRED)
#######################################################################################
add_library(${ROS2_LOOP_RATE_MONITOR_TARGET} STATIC src/Monitor.cpp)
#######################################################################################
target_include_directories(${ROS2_LOOP_RATE_MONITOR_TARGET} PRIVATE include)
#######################################################################################
target_compile_features(${ROS2_LOOP_RATE_MONITOR_TARGET} PRIVATE cxx_std_17)
#######################################################################################
ament_target_dependencies(${ROS2_LOOP_RATE_MONITOR_TARGET} ${THIS_PACKAGE_INCLUDE_DEPENDS})
#######################################################################################
ament_export_targets(${ROS2_LOOP_RATE_MONITOR_TARGET}_export HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
#######################################################################################
install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS ${ROS2_LOOP_RATE_MONITOR_TARGET}
  EXPORT ${ROS2_LOOP_RATE_MONITOR_TARGET}_export
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)
#######################################################################################
ament_package()
#######################################################################################
