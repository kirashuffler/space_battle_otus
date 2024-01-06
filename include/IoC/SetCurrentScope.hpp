#pragma once
#include "../ICommand.hpp"
#include "Common.hpp"
#include "Init.hpp"

namespace ioc {
class SetCurrentScope : public ICommand {
 public:
  SetCurrentScope(std::any scope) : scope_{std::any_cast<Scope>(scope)} {}
  void Execute() override { ioc::Init::current_scope_ = scope_; }

 private:
  Scope scope_;
};
}  // namespace ioc
