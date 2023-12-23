#pragma once
#include "Vector.hpp"

struct SpaceShipProps {
  Vector velocity{};
  Vector position{};
  int directions_number{};
  int direction{};
  int angular_velocity{};
  int angle{};
};
