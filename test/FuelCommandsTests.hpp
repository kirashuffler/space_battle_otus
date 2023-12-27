#pragma once

#include "../include/Adapters/MovableSpaceShip.hpp"
#include "../include/Adapters/SpaceShipWithFuel.hpp"
#include "../include/Commands/BurnFuel.hpp"
#include "../include/Commands/CheckFuel.hpp"
#include "../include/Commands/MacroCommand.hpp"
#include "../include/Commands/Move.hpp"
#include "../include/SpaceShipProps.hpp"
#include "gtest/gtest.h"

TEST(CheckFuel, CheckFuelThrowsExceptionIfNotEnoughFuel) {
  SpaceShipProps space_ship{.fuel_level = 0, .fuel_consumption = 4};
  SpaceShipWithFuel adapter_with_fuel{space_ship};
  CheckFuel cmd{adapter_with_fuel};
  EXPECT_THROW({ cmd.Execute(); }, CheckFuelException);
}

TEST(CheckFuel, CheckFuelDontThrowExceptionIfEnoughFuel) {
  SpaceShipProps space_ship{.fuel_level = 8, .fuel_consumption = 4};
  SpaceShipWithFuel adapter_with_fuel{space_ship};
  CheckFuel cmd{adapter_with_fuel};
  EXPECT_NO_THROW({ cmd.Execute(); });
}

TEST(BurnFuel, BurnFuelMakesLessFuelThanItWasBefore) {
  SpaceShipProps space_ship{.fuel_level = 8, .fuel_consumption = 4};
  SpaceShipWithFuel adapter_with_fuel{space_ship};
  BurnFuel cmd{adapter_with_fuel};
  cmd.Execute();

  auto expected_fuel_level{4};
  EXPECT_EQ(adapter_with_fuel.GetFuelLevel(), expected_fuel_level);
}
