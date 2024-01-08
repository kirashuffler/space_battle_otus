#pragma once
#include <string>

#include "../ICommand.hpp"
#include "Common.hpp"
#include "Core.hpp"

namespace ioc {
class RegisterDependency : public ICommand {
 public:
  RegisterDependency(std::string dependency,
                     IocFunctor dependency_resolver_strategy)
      : dependency_{dependency},
        dependency_resolver_strategy_{dependency_resolver_strategy} {}
  void Execute() override {
    auto current_scope = ioc::Resolve<Scope>("IoC.Scope.Current");
    current_scope->emplace(dependency_, dependency_resolver_strategy_);
  }

 private:
  std::string dependency_;
  IocFunctor dependency_resolver_strategy_;
};
}  // namespace ioc
