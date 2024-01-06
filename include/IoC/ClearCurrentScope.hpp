#pragma once
#include "../ICommand.hpp"
#include "Init.hpp"

namespace ioc {
class ClearCurrentScope : public ICommand {
 public:
  void Execute() override { ioc::Init::current_scope_ = nullptr; }
};
}  // namespace ioc
