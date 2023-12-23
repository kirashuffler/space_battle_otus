#pragma once

#include "IMovable.hpp"
#include "SpaceShipProps.hpp"

class MovableSpaceShip : public IMovable {
 public:
  MovableSpaceShip(SpaceShipProps& space_ship);
  Vector GetLocation() const override;
  Vector GetVelocity() const override;
  void SetLocation(Vector new_position) override;

 private:
  SpaceShipProps space_ship_;
};

MovableSpaceShip::MovableSpaceShip(SpaceShipProps& space_ship)
    : space_ship_{space_ship} {}
Vector MovableSpaceShip::GetLocation() const { return space_ship_.position; }
Vector MovableSpaceShip::GetVelocity() const { return space_ship_.velocity; }
void MovableSpaceShip::SetLocation(Vector new_position) {
  space_ship_.position = new_position;
}
