#pragma once
#include "../include/ICommand.hpp"
#include "../include/IMovable.hpp"
#include "../include/MovableSpaceShip.hpp"
#include "../include/Commands/Move.hpp"
#include "MockedMovable.hpp"
#include "gtest/gtest.h"

TEST(Move, FromOnePointToAnotherUsingVelocity) {
  SCOPED_TRACE("Check move from (12, 5) to (5,8) with velocity (-7,3)");
  Vector start_position{12, 5};
  Vector expected_position{5, 8};
  Vector velocity{-7, 3};
  SpaceShipProps ship{.velocity = velocity, .position = start_position};
  MovableSpaceShip movable_ship_adapter{ship};
  Move move{movable_ship_adapter};
  move.Execute();
  auto is_expected_result =
      movable_ship_adapter.GetLocation() == expected_position;
  EXPECT_EQ(is_expected_result, true);
}

TEST(Move, GetLocationThrowsException) {
  SCOPED_TRACE("Throw an exception if GetLocation is faulty");
  mock::MockedGetLocationError mocked_movable;
  Move move{mocked_movable};
  try {
    move.Execute();
  } catch (const std::runtime_error& e) {
    std::string err_msg{e.what()};
    auto is_expected_result = err_msg == std::string("GetLocationException");
    EXPECT_TRUE(is_expected_result);
  }
}

TEST(Move, GetVelocityThrowsException) {
  SCOPED_TRACE("Throw an exception if GetVelocity is faulty");
  mock::MockedGetVelocityError mocked_movable;
  Move move{mocked_movable};
  try {
    move.Execute();
  } catch (const std::runtime_error& e) {
    std::string err_msg{e.what()};
    auto is_expected_result = err_msg == std::string("GetVelocityException");
    EXPECT_TRUE(is_expected_result);
  }
}

TEST(Move, SetLocationThrowsException) {
  SCOPED_TRACE("Throw an exception if SetLocation is faulty");
  mock::MockedSetLocationError mocked_movable;
  Move move{mocked_movable};
  try {
    move.Execute();
  } catch (const std::runtime_error& e) {
    std::string err_msg{e.what()};
    auto is_expected_result = err_msg == std::string("SetLocationException");
    EXPECT_TRUE(is_expected_result);
  }
}
