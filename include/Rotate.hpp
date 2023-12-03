#pragma once
#include "IRotable.hpp"
#include "ICommand.hpp"
#include <stdexcept>

class Rotate : public ICommand {
public:
  Rotate(IRotable* obj);
  void Execute() override;
private:
  IRotable* obj_;
};

Rotate::Rotate(IRotable* obj)
  : obj_ { obj }
{
}
void Rotate::Execute()
{
  if (!obj_)
    throw std::runtime_error("No object to operate with");
  auto new_direction = (obj_->GetDirection() + obj_->GetAngularVelocity()) % obj_->GetDirectionsNumber();
  obj_->SetDirection(new_direction);
}
