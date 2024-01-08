#pragma once

#include <cmath>
#include <numbers>

#include "../IMovable.hpp"
#include "../SpaceShipProps.hpp"

class MovableWithRotationSpaceShip : public IMovable {
 public:
  MovableWithRotationSpaceShip(SpaceShipProps& space_ship);
  Vector GetLocation() const override;
  Vector GetVelocity() const override;
  void SetLocation(Vector new_position) override;

 private:
  SpaceShipProps& space_ship_;
};

MovableWithRotationSpaceShip::MovableWithRotationSpaceShip(
    SpaceShipProps& space_ship)
    : space_ship_{space_ship} {}
Vector MovableWithRotationSpaceShip::GetLocation() const {
  return space_ship_.position;
}
Vector MovableWithRotationSpaceShip::GetVelocity() const {
  auto v = static_cast<double>(space_ship_.velocity_module);
  auto angle = static_cast<double>(space_ship_.direction) /
               static_cast<double>(space_ship_.directions_number) * 2 *
               std::numbers::pi;

  return {static_cast<int>(v * std::cos(angle)),
          static_cast<int>(v * std::sin(angle))};
}
void MovableWithRotationSpaceShip::SetLocation(Vector new_position) {
  space_ship_.position = new_position;
}
