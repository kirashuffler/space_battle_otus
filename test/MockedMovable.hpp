#pragma once
#include <stdexcept>

#include "../include/IMovable.hpp"

namespace mock {
class MockedGetLocationError : public IMovable {
 public:
  Vector GetLocation() const override {
    throw std::runtime_error("GetLocationException");
  }
  Vector GetVelocity() const override { return {1, 1}; }
  void SetLocation(Vector new_position) override {}
};

class MockedGetVelocityError : public IMovable {
 public:
  Vector GetLocation() const override { return {1, 1}; }

  Vector GetVelocity() const override {
    throw std::runtime_error("GetVelocityException");
  }

  void SetLocation(Vector new_position) override {}
};

class MockedSetLocationError : public IMovable {
 public:
  Vector GetLocation() const override { return {1, 1}; }

  Vector GetVelocity() const override { return {1, 1}; }

  void SetLocation(Vector new_position) override {
    throw std::runtime_error("SetLocationException");
  }
};

}  // namespace mock
