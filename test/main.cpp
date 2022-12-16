#include <memory>

#include <rclcpp/rclcpp.hpp>
#include "gtest/gtest.h"

//#include "../src/hamburger_drive.cpp"

//#include "../include/hamburger_drive.hpp"
// TEST(DummyTests, operationTest){
//   EXPECT_TRUE(true);
// }
// TEST(DummyTests, operationTest1){
//   EXPECT_TRUE(true);
// }

int main(int argc, char ** argv){
  rclcpp::init(argc, argv);
  ::testing::InitGoogleTest(&argc, argv);

  int result = RUN_ALL_TESTS();
  rclcpp::shutdown();
  return result;
}
