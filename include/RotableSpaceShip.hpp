#pragma once

#include "IRotable.hpp"
#include "SpaceShipProps.hpp"

class RotableSpaceShip : public IRotable {
  public:
    RotableSpaceShip(SpaceShipProps& space_ship);
    int GetDirection() const override;
    int GetAngularVelocity() const override;
    int GetDirectionsNumber() const override;
    void SetDirection(int new_direction) override;
  private:
    SpaceShipProps& space_ship_;
};

RotableSpaceShip::RotableSpaceShip(SpaceShipProps& space_ship)
  : space_ship_ { space_ship }
{
}
int RotableSpaceShip::GetDirection() const
{
  return space_ship_.direction;
}
int RotableSpaceShip::GetAngularVelocity() const
{
  return space_ship_.angular_velocity;
}
void RotableSpaceShip::SetDirection(int new_direction)
{
  space_ship_.direction = new_direction;
}
int RotableSpaceShip::GetDirectionsNumber() const
{
  if (!space_ship_.directions_number)
    throw std::runtime_error("GetDirectionsNumberException: zero value is forbidden");
  return space_ship_.directions_number;
}
