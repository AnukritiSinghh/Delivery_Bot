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


#include "../include/turtlebot3_walker/walker.hpp"

Walker::Walker()
    : Node("walker"),
      left_dist_(0.0),
      center_dist_(0.0),
      right_dist_(0.0),
      state_(STOP) \{
      auto pubTopicName = "cmd_vel";
      publisher_ = this->create_publisher<TWIST> (pubTopicName, 10);
       auto subTopicName = "/scan"; 
       auto subCallback = std::bind(&Walker::scan_callback, this, _1); 
       subscription_ = this->create_subscription<SCAN> 
                    (subTopicName, 10, subCallback); 
 
       auto processCallback = std::bind(&Walker::process_callback, this); 
       timer_ = this->create_wall_timer(100ms, processCallback ); 
\} 
 
void Walker::scan_callback(const SCAN& msg) \{ 
    lastscan_ = msg; 
\} 
 
void Walker::process_callback() \{ 
    // Do nothing until the first scan data is read. 
    if (lastscan_.header.stamp.sec == 0) 
      return; 
 
    // Create the message to publish (initialized to all 0) 
    auto message = TWIST(); 
 
    switch (state_) \{ 
        case FORWARD: 
        if (obstacle_detected()) \{ 
            state_ = STOP; 
            message.linear.x = 0.0; 
            message.linear.y = 0.0; 
            message.linear.z = 0.0; 
            publisher_->publish(message); 
            RCLCPP_INFO_STREAM(this->get_logger(), "State = STOP"); 
        \} 
        break; 
 
        case STOP: 
        if (obstacle_detected()) \{ 
            state_ = TURN; 
            message.angular.z = 0.1; 
            publisher_->publish(message); 
            RCLCPP_INFO_STREAM(this->get_logger(), "State = TURN"); 
        \} else \{ 
            state_ = FORWARD; 
            message.linear.x = -0.1; 
            publisher_->publish(message); 
            RCLCPP_INFO_STREAM(this->get_logger(), "State = FORWARD"); 
        \} 
        break; 
 
        case TURN: 
        if (!obstacle_detected()) \{ 
            state_ = FORWARD; 
            message.linear.x = -0.2; 
            publisher_->publish(message); 
            RCLCPP_INFO_STREAM(this->get_logger(), "State = FORWARD"); 
        \} 
        break; 
    \} 
\} 
 
bool Walker::obstacle_detected() \{ 
    // non-zero minimium angle with laser scan 
    if (scan_.angle_min != 0) \{ 
        auto ray_idx = static_cast<int>( 
            (scan_.angle_max - scan_.angle_min)/(scan_.angle_increment) - 1); 
        center_ = scan_.ranges[ray_idx]; 
        right_ = scan_.ranges[ray_idx + 25]; 
        left_ = scan_.ranges[ray_idx - 25]; 
    \} else \{ 
        auto ray_idx = 0; 
        center_ = scan_.ranges[ray_idx]; 
        left_ = scan_.ranges[(scan_.angle_max/scan_.angle_increment) - 25]; 
        right_ = scan_.ranges[ray_idx + 25]; 
    \} 
 
    RCLCPP_INFO_STREAM(this->get_logger(), "Distance: " << left_ << " " << center_ << " " << right_); 
 
    if (left_< 0.8 || center_< 0.8 || right_< 0.8) \{ 
        RCLCPP_INFO_STREAM(this->get_logger(), "can't go forward, obstacle!"); 
        return true; 
    \} 
 
    return false; 
\} 
 
int main(int argc, char * argv[]) \{ 
  rclcpp::init(argc, argv); 
  rclcpp::spin(std::make_shared<Walker>()); 
  rclcpp::shutdown(); 
  return 0; 
\} 
 
}
 
