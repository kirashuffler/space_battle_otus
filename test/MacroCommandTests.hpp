#pragma once
#include <iostream>

#include "../include/Adapters/MovableWithRotationSpaceShip.hpp"
#include "../include/Adapters/RotableSpaceShip.hpp"
#include "../include/Adapters/SpaceShipWithFuel.hpp"
#include "../include/Commands/BurnFuel.hpp"
#include "../include/Commands/CheckFuel.hpp"
#include "../include/Commands/MacroCommand.hpp"
#include "../include/Commands/Move.hpp"
#include "../include/Commands/Rotate.hpp"
#include "../include/SpaceShipProps.hpp"
#include "gtest/gtest.h"

TEST(MacroCommand, MoveBurnCommandsTest) {
  SpaceShipProps space_ship{
      .velocity{1, 1}, .position{0, 0}, .fuel_level = 5, .fuel_consumption = 1};
  MovableSpaceShip move_adapter{space_ship};
  SpaceShipWithFuel fuel_adapter{space_ship};

  std::vector<CommandPtr> commands;
  commands.emplace_back(std::make_unique<CheckFuel>(fuel_adapter));
  commands.emplace_back(std::make_unique<Move>(move_adapter));
  commands.emplace_back(std::make_unique<BurnFuel>(fuel_adapter));
  MacroCommand move_with_fuel{std::move(commands)};

  move_with_fuel.Execute();
  EXPECT_EQ(move_adapter.GetLocation().x, 1);
  EXPECT_EQ(move_adapter.GetLocation().y, 1);
  EXPECT_EQ(fuel_adapter.GetFuelLevel(), 4);
}

TEST(MacroCommand, RotateMoveCommandsTest) {
  SpaceShipProps space_ship{.velocity_module = 5,
                            .position{1, 1},
                            .directions_number = 8,
                            .direction = 0,
                            .angular_velocity = 4,
                            .fuel_level = 5,
                            .fuel_consumption = 1};
  MovableWithRotationSpaceShip move_adapter{space_ship};
  RotableSpaceShip rotate_adapter{space_ship};

  auto start_pos = move_adapter.GetLocation();

  auto velocity_vector{move_adapter.GetVelocity()};
  Vector expected_velocity{5, 0};
  EXPECT_EQ(velocity_vector, expected_velocity);

  std::vector<CommandPtr> commands;
  commands.emplace_back(std::make_unique<Rotate>(rotate_adapter));
  commands.emplace_back(std::make_unique<Move>(move_adapter));
  MacroCommand move_with_rotation{std::move(commands)};
  move_with_rotation.Execute();

  velocity_vector = move_adapter.GetVelocity();
  expected_velocity = {-5, 0};
  EXPECT_EQ(velocity_vector, expected_velocity);

  Vector expected_position = start_pos + expected_velocity;
  EXPECT_EQ(move_adapter.GetLocation(), expected_position);
}
