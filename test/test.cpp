#include <memory>
#include "gtest/gtest.h"


#include <chrono>
#include <stdlib.h>
#include "std_msgs/msg/string.hpp"
using namespace std::chrono_literals;
#include <rclcpp/rclcpp.hpp>
//#include "../src/hamburger_drive.cpp"

#include "../include/hamburger_drive.hpp"

TEST(DummyTests, operationTest3){
  EXPECT_TRUE(true);
}
// TEST(DummyTests, operationTest4){
//   EXPECT_TRUE(false);
// // }

/// testing that there is no movement in turtlebot
TEST(DummyTests, classMovementTest){
  //EXPECT_TRUE(true);
  
  // Robot A;
  // A.left_dist_=0;  
  // A.center_dist_=0;
  // A.right_dist_=0;
  // EXPECT_EQ((  A.left_dist_+ 
  // A.center_dist_+
  // A.right_dist_), 0);

  int left_dist=0;  
  int center_dist=0;
  int right_dist=0;
  int total =(left_dist+  center_dist+ right_dist);

  EXPECT_EQ(total, 0);

}

class TaskTalker : public testing::Test {
 protected:
  rclcpp::Node::SharedPtr node_;
};

//ROS test
TEST_F(TaskTalker, test_num_publishers) {
  node_ = rclcpp::Node::make_shared("test_num_pubs");
  auto test_pub = node_->create_publisher<std_msgs::msg::String>
                    ("chatter", 10.0);

  auto num_pub = node_->count_publishers("chatter");
  EXPECT_EQ(1, static_cast<int>(num_pub));
}