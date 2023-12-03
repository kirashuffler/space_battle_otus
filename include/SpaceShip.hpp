#pragma once
#include "Vector.hpp"

struct SpaceShipProps {
  Vector velocity {};
  Vector position {};
  double directions_number {};
  double direction {};
  double angular_velocity;
  double angle;
};
