#pragma once
#include <any>
#include <string>
#include <vector>

namespace ioc {
class IDependencyResolver {
 public:
  virtual std::any Resolve(std::string dependency,
                           std::vector<std::any> args) = 0;
  ~IDependencyResolver() = default;
};
}  // namespace ioc
