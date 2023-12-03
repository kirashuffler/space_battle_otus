#include <iostream>
#include <vector>
#include <math.h>
#include <stdexcept>
#include <limits>

constexpr double e = 10e-6;
constexpr double kInfinity = std::numeric_limits<double>::infinity();
const double kNan = std::nan("");
bool isZero(double value){
  return (value - e <= 0) && (value + e >= 0);
}

bool lessThanZero(double value){
  return value < -e;
}

bool greaterThanZero(double value){
  return value > e;
}

std::vector<double> QuadraticEquationSolve(double a, double b, double c){
  if (std::abs(a) >= kInfinity - e ||
      std::abs(b) >= kInfinity - e || 
      std::abs(c) >= kInfinity - e
      )
    throw std::runtime_error("Coefficients must not be an infinite value");

  if (isnan(a) || isnan(b) || isnan(c))
    throw std::runtime_error("Coefficients must not be an nan value");

  if (isZero(a))
    throw std::runtime_error("Coefficient 'a' must not be zero");

  std::vector<double> solutions;
  auto D = b*b - 4 * a * c;

  if (lessThanZero(D))
    return solutions;

  if (isZero(D)){
    auto x = (-b) / (2 * a);
    solutions.emplace_back(x);
    return solutions;
  }

  auto x1 = (-b + sqrt(D)) / (2 * a);
  auto x2 = (-b - sqrt(D)) / (2 * a);
  solutions.emplace_back(x1);
  solutions.emplace_back(x2);
  return solutions;
}
