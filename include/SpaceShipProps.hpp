#pragma once
#include "Vector.hpp"

struct SpaceShipProps {
  Vector velocity{};
  int velocity_module{};
  Vector position{};
  int directions_number{};
  int direction{};
  int angular_velocity{};
  int fuel_level{};
  int fuel_consumption{};
};
