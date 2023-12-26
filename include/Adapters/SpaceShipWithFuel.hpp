#pragma once
#include "../IFuelable.hpp"
#include "../SpaceShipProps.hpp"

class SpaceShipWithFuel : public IFuelable {
 public:
  SpaceShipWithFuel(SpaceShipProps& space_ship);
  int GetFuelLevel() const override;
  void SetFuelLevel(int fuel_level) override;
  int GetFuelConsumption() const override;

 private:
  SpaceShipProps& space_ship_;
};
SpaceShipWithFuel::SpaceShipWithFuel(SpaceShipProps& space_ship)
    : space_ship_{space_ship} {}
int SpaceShipWithFuel::GetFuelLevel() const { return space_ship_.fuel_level; }
void SpaceShipWithFuel::SetFuelLevel(int fuel_level) {
  space_ship_.fuel_level = fuel_level;
}
int SpaceShipWithFuel::GetFuelConsumption() const {
  return space_ship_.fuel_consumption;
}
