#pragma once
#include "Vector.hpp"

struct IMovable {
  virtual Vector GetLocation() const = 0;
  virtual Vector GetVelocity() const = 0;
  virtual void SetLocation(Vector new_position) = 0;
  virtual ~IMovable() = default;
};
