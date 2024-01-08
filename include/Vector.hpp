#pragma once
#include <ostream>

struct Vector {
  int x, y;
  Vector operator+(const Vector& other) const {
    return {x + other.x, y + other.y};
  }
  Vector operator-(const Vector& other) const {
    return {x - other.x, y - other.y};
  }
  bool operator==(const Vector& other) const {
    return x == other.x && y == other.y;
  }
  friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
  }
};
