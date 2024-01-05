#pragma once
#include <any>
#include <vector>
#include <string>

namespace ioc {
  class IDependencyResolver {
  public:
    virtual std::any Resolve(std::string dependency, std::vector<std::any> args) = 0;
    ~IDependencyResolver() = default;
  };
}
