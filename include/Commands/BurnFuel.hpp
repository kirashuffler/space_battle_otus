#pragma once
#include "../ICommand.hpp"
#include "../IFuelable.hpp"

class BurnFuel : public ICommand {
 public:
  BurnFuel(IFuelable& obj) : obj_{obj} {}
  void Execute() {
    obj_.SetFuelLevel(obj_.GetFuelLevel() - obj_.GetFuelConsumption());
  }

 private:
  IFuelable& obj_;
};
