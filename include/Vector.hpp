#pragma once

struct Vector {
  int x, y;
  Vector operator+(const Vector& other) const {
    return {x + other.x, y + other.y};
  }
  bool operator==(const Vector& other) const {
    return x == other.x && y == other.y;
  }
};
