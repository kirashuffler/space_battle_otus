#pragma once
#include "../include/IoC/Core.hpp"
#include "../include/IoC/DependencyResolver.hpp"
#include "gtest/gtest.h"

TEST(Core, IocShouldUpdateResolveDependencyStrategy) {
  bool was_called = false;
  ioc::IocStrategyUpdater updater =
      [&was_called](ioc::IocStrategy args) -> ioc::IocStrategy {
    was_called = true;
    return args;
  };
  auto cmd = ioc::Resolve<CommandPtr>("Update Ioc Resolve Dependency Strategy",
                                      {updater});
  cmd->Execute();
  EXPECT_TRUE(was_called);
}

TEST(Core, IocShouldThrowExceptionIfDependencyIsNotFound) {
  EXPECT_THROW({ ioc::Resolve<std::any>("UnexistingDependency", {}); },
               std::runtime_error);
}

TEST(Core, IocShouldThrowBadCastException) {
  ioc::IocStrategyUpdater updater =
      [](ioc::IocStrategy args) -> ioc::IocStrategy { return args; };
  EXPECT_THROW(
      {
        ioc::Resolve<int>("Update Ioc Resolve Dependency Strategy", {updater});
      },
      std::bad_cast);
}
