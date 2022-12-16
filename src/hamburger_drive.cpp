// Copyright 2022 Mayank Sharma, Joshua Gomez, Anukriti Singh
//
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
 * @file hamburger_drive.cpp
 * @author Mayank Sharma, Joshua Gomez, Anukriti Singh
 * @brief Implementation of the Tb3Walker class methods
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/hamburger_drive.hpp"

Robot::Robot()
    : Node("walker"),
      left_dist_(0.0),
      center_dist_(0.0),
      right_dist_(0.0),
      state_(STOP) {
       auto pubTopicName = "cmd_vel";
       publisher_ = this->create_publisher<TWIST> (pubTopicName, 10);

       auto subTopicName = "/scan";
       auto subCallback = std::bind(&Robot::scan_callback, this, _1);
       subscription_ = this->create_subscription<SCAN>
                    (subTopicName, 10, subCallback);

       auto timerCallback = std::bind(&Robot::timer_callback, this);
       timer_ = this->create_wall_timer(100ms, timerCallback);
}

void Robot::scan_callback(const SCAN& msg) {
    scan_ = msg;
}

void Robot::timer_callback() {
    // wait until the first scan data is read.
    if (scan_.header.stamp.sec == 0)
      return;

    auto message = TWIST();

    switch (state_) {
        case FORWARD:
        if (detect_obstacle()) {
            state_ = STOP;
            message.linear.x = 0.0;
            message.linear.y = 0.0;
            message.linear.z = 0.0;
            publisher_->publish(message);
            RCLCPP_INFO_STREAM(this->get_logger(), "State = STOP");
        }
        break;

        case STOP:
        if (detect_obstacle()) {
            state_ = TURN;
            message.angular.z = 0.1;
            publisher_->publish(message);
            RCLCPP_INFO_STREAM(this->get_logger(), "State = TURN");
        } else {
            state_ = FORWARD;
            message.linear.x = 0.2;
            publisher_->publish(message);
            RCLCPP_INFO_STREAM(this->get_logger(), "State = FORWARD");
        }
        break;

        case TURN:
        if (!detect_obstacle()) {
            state_ = FORWARD;
            message.linear.x = 0.2;
            publisher_->publish(message);
            RCLCPP_INFO_STREAM(this->get_logger(), "State = FORWARD");
        }
        break;
    }
}

bool Robot::detect_obstacle() {
    // For laser scans with non-zero minimium angle
    if (scan_.angle_min != 0) {
        // Index for the center laser scan ray
        auto ray_idx = static_cast<int>(
            (scan_.angle_max - scan_.angle_min)/(scan_.angle_increment) - 1);
        center_dist_ = scan_.ranges[ray_idx];
        left_dist_ = scan_.ranges[ray_idx - 25];
        right_dist_ = scan_.ranges[ray_idx + 25];
    } else {
        auto ray_idx = 0;
        center_dist_ = scan_.ranges[ray_idx];
        left_dist_ =
                    scan_.ranges[(scan_.angle_max/scan_.angle_increment) - 25];
        right_dist_ = scan_.ranges[ray_idx + 25];
    }

    RCLCPP_INFO_STREAM(this->get_logger(), "Distance: " << left_dist_ <<
                 " " << center_dist_ << " " << right_dist_);

    // Obstacle is detected if either of the laser scan rays picks up one.
    if (left_dist_ < 0.8 || center_dist_ < 0.8 || right_dist_ < 0.8) {
        RCLCPP_INFO_STREAM(this->get_logger(), "Obstacle detected!");
        return true;
    }

    return false;
}

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Robot>());
  rclcpp::shutdown();
  return 0;
}
