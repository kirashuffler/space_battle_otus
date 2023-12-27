#pragma once

class IFuelable {
 public:
  virtual int GetFuelLevel() const = 0;
  virtual void SetFuelLevel(int) = 0;
  virtual int GetFuelConsumption() const = 0;
  virtual ~IFuelable() = default;
};
