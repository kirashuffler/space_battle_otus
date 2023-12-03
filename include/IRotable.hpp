#pragma once

struct IRotable {
  virtual int GetDirection() const = 0;
  virtual int GetAngularVelocity() const = 0;
  virtual int GetDirectionsNumber() const = 0;
  virtual void SetDirection(int new_direction) = 0;
  ~IRotable() = default;
};
