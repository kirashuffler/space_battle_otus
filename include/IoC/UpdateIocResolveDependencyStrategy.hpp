#pragma once
#include "../ICommand.hpp"
#include "Common.hpp"
#include "Core.hpp"

namespace ioc {
  namespace core {
    extern IocStrategy strategy;
  }
  class UpdateIocResolveDependencyStrategy : public ICommand {
  public:
    UpdateIocResolveDependencyStrategy(IocStrategyUpdater updater)
      : update_ioc_strategy_{updater} {}
    void Execute() override {
      ioc::core::strategy = update_ioc_strategy_(ioc::core::strategy);
    }
  private:
    IocStrategyUpdater update_ioc_strategy_;
  };
}
