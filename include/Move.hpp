#pragma once
#include "IMovable.hpp"
#include "ICommand.hpp"
#include <stdexcept>

class Move : public ICommand {
public:
  Move(IMovable* obj);
  void Execute() override;
private:
  IMovable* obj_;
};

Move::Move(IMovable* obj)
  : obj_ { (IMovable*)obj }
{
}
void Move::Execute()
{
  if (!obj_)
    throw std::runtime_error("No object to operate with");
  auto new_position = obj_->GetLocation() + obj_->GetVelocity();
  obj_->SetLocation(new_position);
}

