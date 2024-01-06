#pragma once
#include <sstream>
#include <string>

#include "../ICommand.hpp"
#include "Common.hpp"
#include "UpdateIocResolveDependencyStrategy.hpp"

namespace ioc {

namespace core {
inline IocStrategy strategy = [](std::string dependency,
                                 ArgsVec args) -> std::any {
  if (dependency == "Update Ioc Resolve Dependency Strategy") {
    auto updating_strategy = std::any_cast<IocStrategyUpdater>(args[0]);
    return MakeCommand<UpdateIocResolveDependencyStrategy>(updating_strategy);
  } else {
    std::stringstream err;
    err << "Dependency " << dependency << "not found in Ioc.\n";
    throw std::runtime_error(err.str().c_str());
  }
};

template <typename T>
inline T Resolve(std::string dependency, ArgsVec args = {}) {
  auto res = strategy(dependency, args);
  return std::any_cast<T>(res);
}
}  // namespace core
}  // namespace ioc
