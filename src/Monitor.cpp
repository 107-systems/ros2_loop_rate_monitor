/**
 * Copyright (c) 2023 LXRobotics GmbH.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/ros2_loop_rate_monitor/graphs/contributors.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <ros2_loop_rate_monitor/Monitor.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace loop_rate
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

Monitor::Monitor(std::chrono::milliseconds const loop_duration_target,
                 std::chrono::milliseconds const loop_duration_epsilon)
: LOOP_DURATION_TARGET{loop_duration_target}
, LOOP_DURATION_EPSILON{loop_duration_epsilon}
, _prev_loop_timepoint{std::chrono::steady_clock::now()}
, _is_prev_loop_timepoint_valid{false}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

void Monitor::update()
{
  auto const now = std::chrono::steady_clock::now();
  _prev_loop_timepoint = now;
  _is_prev_loop_timepoint_valid = true;
}

std::tuple<Monitor::Timeout, std::optional<std::chrono::milliseconds>> Monitor::isTimeout()
{
  if (!_is_prev_loop_timepoint_valid)
    return std::make_tuple(Timeout::UpdateNotCalled, std::nullopt);

  auto const now = std::chrono::steady_clock::now();
  auto const actual_loop_duration = (now - _prev_loop_timepoint);

  if (actual_loop_duration < (LOOP_DURATION_TARGET + LOOP_DURATION_EPSILON))
    return std::make_tuple(Timeout::No, std::nullopt);

  return std::make_tuple(Timeout::No, std::chrono::duration_cast<std::chrono::milliseconds>(actual_loop_duration));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* loop_rate */
