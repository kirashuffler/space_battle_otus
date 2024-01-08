#pragma once
#include <iostream>
#include <sstream>

#include "Common.hpp"
#include "IDependencyResolver.hpp"

namespace ioc {
class DependencyResolver : public IDependencyResolver {
 public:
  DependencyResolver(std::any scope) { scope_ = std::any_cast<Scope>(scope); }
  std::any Resolve(std::string dependency,
                   std::vector<std::any> args = {}) override {
    auto cur_scope = scope_;
    while (true) {
      if (cur_scope->contains(dependency)) {
        return cur_scope->at(dependency)(args);
      } else {
        try {
          cur_scope =
              std::any_cast<Scope>(cur_scope->at("IoC.Scope.Parent")(args));
        } catch (std::runtime_error& e) {
          std::stringstream ss;
          ss << "Dependency '" << dependency << "' is not registered\n";
          throw std::runtime_error(ss.str().c_str());
        }
      }
    }
  }

 private:
  Scope scope_;
};
}  // namespace ioc
