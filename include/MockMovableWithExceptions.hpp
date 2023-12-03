#pragma once
#include "IMovable.hpp"
#include <stdexcept>

class MockMovableWithExceptions : IMovable {
public:
  Vector GetLocation() const override {
    throw std::runtime_error("GetLocationException");
  }
  Vector GetVelocity() const override {
    throw std::runtime_error("GetVelocityException");
  }
  void SetLocation(Vector new_position) override {
    throw std::runtime_error("SetLocationException");
  }
};
