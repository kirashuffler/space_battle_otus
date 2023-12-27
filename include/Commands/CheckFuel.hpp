#pragma once
#include "../ICommand.hpp"
#include "../IFuelable.hpp"

DEFINE_EXCEPTION(CheckFuelException);

class CheckFuel : public ICommand {
 public:
  CheckFuel(IFuelable& obj) : obj_{obj} {}
  void Execute() {
    if (obj_.GetFuelLevel() < obj_.GetFuelConsumption())
      throw CheckFuelException("");
  }

 private:
  IFuelable& obj_;
};
