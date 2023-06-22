/**
 * Copyright (c) 2023 LXRobotics GmbH.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/ros2_loop_rate_monitor/graphs/contributors.
 */

#pragma once

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <tuple>
#include <string>
#include <chrono>
#include <memory>
#include <optional>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace loop_rate
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class Monitor
{
public:
  typedef std::shared_ptr<Monitor> SharedPtr;

  static SharedPtr create(std::chrono::milliseconds const loop_duration_target) {
    return std::make_shared<Monitor>(loop_duration_target, std::chrono::milliseconds(0));
  }
  static SharedPtr create(std::chrono::milliseconds const loop_duration_target, std::chrono::milliseconds const loop_duration_epsilon) {
    return std::make_shared<Monitor>(loop_duration_target, loop_duration_epsilon);
  }


  Monitor(std::chrono::milliseconds const loop_duration_target,
          std::chrono::milliseconds const loop_duration_epsilon);


  void update();

  enum class Timeout { Yes, No, UpdateNotCalled };
  std::tuple<Timeout, std::optional<std::chrono::milliseconds>> isTimeout();


private:
  std::chrono::milliseconds const LOOP_DURATION_TARGET;
  std::chrono::milliseconds const LOOP_DURATION_EPSILON;
  std::chrono::steady_clock::time_point _prev_loop_timepoint;
  bool _is_prev_loop_timepoint_valid;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* loop_rate */
