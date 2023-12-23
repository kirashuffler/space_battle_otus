#pragma once

#include "../include/ICommand.hpp"
#include "../include/IRotable.hpp"
#include "../include/RotableSpaceShip.hpp"
#include "../include/Commands/Rotate.hpp"
#include "MockedRotable.hpp"
#include "gtest/gtest.h"

TEST(Rotate, RotateWithSomeAngularVelocity) {
  SCOPED_TRACE(
      "Check direction change from 1 to 3 with angular velocity 2 and 8 "
      "directions");
  SpaceShipProps ship{
      .directions_number = 8, .direction = 1, .angular_velocity = 2};
  RotableSpaceShip rotable_ship_adapter{ship};
  Rotate rotate{rotable_ship_adapter};
  rotate.Execute();
  auto expected_new_direction = 3;
  EXPECT_EQ(rotable_ship_adapter.GetDirection(), 3);
}

TEST(Rotate, RotateWithDirectionOverflow) {
  SCOPED_TRACE(
      "Check direction change from 1 to 3 with angular velocity 10 and 8 "
      "directions");
  SpaceShipProps ship{
      .directions_number = 8, .direction = 1, .angular_velocity = 10};
  RotableSpaceShip rotable_ship_adapter{ship};
  Rotate rotate{rotable_ship_adapter};
  rotate.Execute();
  auto expected_new_direction = 3;
  EXPECT_EQ(rotable_ship_adapter.GetDirection(), 3);
}

TEST(Rotate, RotateWithDirectionZeroValue) {
  SCOPED_TRACE(
      "Check for floating point exception if directions_number is zero");
  SpaceShipProps ship{
      .directions_number = 8, .direction = 0, .angular_velocity = 10};
  RotableSpaceShip rotable_ship_adapter{ship};
  Rotate rotate{rotable_ship_adapter};
  try {
    rotate.Execute();
  } catch (std::runtime_error& e) {
    std::string err_msg{e.what()};
    auto is_expected_result =
        err_msg ==
        std::string("GetDirectionsNumberException: zero value is forbidden");
    EXPECT_TRUE(is_expected_result);
  }
}

TEST(Rotate, GetDirectionThrowsException) {
  SCOPED_TRACE("Throw an exception if GetDirection is faulty");
  mock::MockedGetDirectionError mocked_rotable;
  Rotate rotate{mocked_rotable};
  try {
    rotate.Execute();
  } catch (const std::runtime_error& e) {
    std::string err_msg{e.what()};
    auto is_expected_result = err_msg == std::string("GetDirectionException");
    EXPECT_TRUE(is_expected_result);
  }
}

TEST(Rotate, GetAngularVelocityThrowsException) {
  SCOPED_TRACE("Throw an exception if GetAngularVelocity is faulty");
  mock::MockedGetAngularVelocityError mocked_rotable;
  Rotate rotate{mocked_rotable};
  try {
    rotate.Execute();
  } catch (const std::runtime_error& e) {
    std::string err_msg{e.what()};
    auto is_expected_result =
        err_msg == std::string("GetAngularVelocityException");
    EXPECT_TRUE(is_expected_result);
  }
}

TEST(Rotate, GetDirectionsNumberThrowsException) {
  SCOPED_TRACE("Throw an exception if GetDirectionsNumber is faulty");
  mock::MockedGetDirectionsNumberError mocked_rotable;
  Rotate rotate{mocked_rotable};
  try {
    rotate.Execute();
  } catch (const std::runtime_error& e) {
    std::string err_msg{e.what()};
    auto is_expected_result =
        err_msg == std::string("GetDirectionsNumberException");
    EXPECT_TRUE(is_expected_result);
  }
}
TEST(Rotate, SetDirectionThrowsException) {
  SCOPED_TRACE("Throw an exception if SetDirection is faulty");
  mock::MockedSetDirectionError mocked_rotable;
  Rotate rotate{mocked_rotable};
  try {
    rotate.Execute();
  } catch (const std::runtime_error& e) {
    std::string err_msg{e.what()};
    auto is_expected_result = err_msg == std::string("SetDirectionException");
    EXPECT_TRUE(is_expected_result);
  }
}
