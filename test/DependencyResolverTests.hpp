#pragma once
#include "../include/IoC/DependencyResolver.hpp"
#include "../include/IoC/Core.hpp"
#include "gtest/gtest.h"

TEST(DependencyResolver, Test){
  ioc::DependenciesMap scope;
  scope["Dependency1"] = [](ioc::ArgsVec args)->std::any {
    return 0;
  };
  ioc::DependencyResolver resolver{scope};
  auto v = std::any_cast<int>(resolver.Resolve("Dependency1", {}));
  EXPECT_EQ(v, 0);
}

TEST(Core, IocShouldUpdateResolveDependencyStrategy){
  bool was_called = false;
  ioc::IocStrategyUpdater updater = 
  [&was_called](ioc::IocStrategy args)->ioc::IocStrategy { 
    was_called = true; 
    return args;
  };
  auto cmd = ioc::core::Resolve<CommandPtr>(
      "Update Ioc Resolve Dependency Strategy",
      {updater}
  );
  cmd->Execute();
  EXPECT_TRUE(was_called);
}
