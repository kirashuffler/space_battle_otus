#pragma once
#include <thread>

#include "../ICommand.hpp"
#include "Common.hpp"

namespace ioc {
class Init : public ICommand {
 public:
  void Execute() override;
  friend class ClearCurrentScope;
  friend class SetCurrentScope;

 private:
  static inline Scope root_scope_{std::make_shared<DependenciesMap>()};
  static inline Scope current_scope_;
  static inline bool already_successfully_{false};
  static inline std::mutex root_scope_mtx_;
};
}  // namespace ioc
