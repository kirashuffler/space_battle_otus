#pragma once
#include "Common.hpp"
#include "IDependencyResolver.hpp"

namespace ioc {
class DependencyResolver : public IDependencyResolver {
 public:
  DependencyResolver(std::any scope) {
    dependencies_ = std::any_cast<DependenciesMap>(scope);
  }
  std::any Resolve(std::string dependency,
                   std::vector<std::any> args) override {
    DependenciesMap* dependencies = &dependencies_;
    while (true) {
      if (dependencies->contains(dependency)) {
        return dependencies->at(dependency)(args);
      } else {
        dependencies = (std::any_cast<DependenciesMap*>(
            dependencies_.at("IoC.Scope.Parent")(args)));
      }
    }
  }

 private:
  std::unordered_map<std::string, IocFunctor> dependencies_;
};
}  // namespace ioc
