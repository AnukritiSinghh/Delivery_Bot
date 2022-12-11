// Copyright 2022 Anukriti Singh, Joshua Gomes, Mayank Sharma.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0 
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
/**
 * @file Walker.hpp
 * @author Anukriti Singh, Joshua Gomes, Mayank Sharma
 * @brief Turtlebot3 
 * @version 1
 * @date 2022-12-09
 * @copyright Copyright (c) 2022
 */

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>

using std::placeholders::_1;
using namespace std::chrono_literals;

using SCAN = sensor_msgs::msg::LaserScan;
using TWIST = geometry_msgs::msg::Twist;

// using a State Machine
typedef enum {
  FORWARD = 0,
  STOP,
  TURN,
} StateType;

class Walker : public rclcpp::Node {
 public:
    Walker();

 private:
    /**
     * @brief Callback function
     * 
     */
    void process_callback();

    /**
     * @brief Callback function for laser scan data
     * 
     */
    void scan_callback(const SCAN&);

    /**
     * @brief Function to detect obstacle
     * @return False if obstacle is not detected
     * @return True if obstacle is detected
     */
    bool detect_obstacle();

    rclcpp::Publisher<TWIST>::SharedPtr publisher_;
    rclcpp::Subscription<SCAN>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;

    SCAN scan_;  // To store laser scan data
    float left_; // Left side
    float center_; // Center 
    float right_; // Right side
    StateType state_;
};
