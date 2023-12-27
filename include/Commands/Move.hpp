#pragma once
#include <stdexcept>

#include "../ICommand.hpp"
#include "../IMovable.hpp"

class Move : public ICommand {
 public:
  Move(IMovable& obj);
  void Execute() override;

 private:
  IMovable& obj_;
};

Move::Move(IMovable& obj) : obj_{obj} {}
void Move::Execute() {
  auto new_position = obj_.GetLocation() + obj_.GetVelocity();
  obj_.SetLocation(new_position);
}
