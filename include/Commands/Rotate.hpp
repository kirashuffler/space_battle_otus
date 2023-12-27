#pragma once
#include <stdexcept>

#include "../ICommand.hpp"
#include "../IRotable.hpp"

class Rotate : public ICommand {
 public:
  Rotate(IRotable& obj);
  void Execute() override;

 private:
  IRotable& obj_;
};

Rotate::Rotate(IRotable& obj) : obj_{obj} {}
void Rotate::Execute() {
  auto new_direction = (obj_.GetDirection() + obj_.GetAngularVelocity()) %
                       obj_.GetDirectionsNumber();
  obj_.SetDirection(new_direction);
}
