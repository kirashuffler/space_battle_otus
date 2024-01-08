#pragma once
#include "../include/IoC/Ioc.hpp"

class ScopeTest : public testing::Test {
 protected:
  void SetUp() override {
    MakeCommand<ioc::Init>()->Execute();
    auto ioc_scope = ioc::Resolve<std::any>("IoC.Scope.Create");
    ioc::Resolve<CommandPtr>("IoC.Scope.Current.Set", {ioc_scope})->Execute();
  }
  void TearDown() override {
    ioc::Resolve<CommandPtr>("IoC.Scope.Current.Clear")->Execute();
  }
};

TEST_F(ScopeTest, IocShouldThrowExceptionOnResolvingParentScopeForRootScope) {
  auto parent_scope = ioc::Resolve<std::any>("IoC.Scope.Parent");
  ioc::Resolve<CommandPtr>("IoC.Scope.Current.Set", {parent_scope})->Execute();
  EXPECT_THROW({ ioc::Resolve<ioc::Scope>("IoC.Scope.Parent"); },
               std::runtime_error);
}

TEST_F(ScopeTest, IocShouldResolveRegisteredDependencyInCurrentScope) {
  ioc::Resolve<CommandPtr>(
      "IoC.Register",
      {"someDependency", static_cast<ioc::IocFunctor>(
                             [](ioc::ArgsVec args) -> std::any { return 1; })})
      ->Execute();
  EXPECT_EQ(1, ioc::Resolve<int>("someDependency"));
}

TEST_F(ScopeTest,
       IocShouldThrowExceptionOnUnregisteredDependencyInCurrentScope) {
  EXPECT_THROW({ ioc::Resolve<int>("someDependency"); }, std::runtime_error);
}

TEST_F(ScopeTest,
       IocShouldUseParentScopeIfResolvingDependencyIsNotDefinedInCurrentScope) {
  ioc::Resolve<CommandPtr>(
      "IoC.Register",
      {"someDependency", static_cast<ioc::IocFunctor>(
                             [](ioc::ArgsVec args) -> std::any { return 1; })})
      ->Execute();
  auto parent_scope = ioc::Resolve<ioc::Scope>("IoC.Scope.Current");
  auto ioc_scope = ioc::Resolve<ioc::Scope>("IoC.Scope.Create");
  ioc::Resolve<CommandPtr>("IoC.Scope.Current.Set", {ioc_scope})->Execute();
  EXPECT_EQ(ioc_scope, ioc::Resolve<ioc::Scope>("IoC.Scope.Current"));
  EXPECT_EQ(1, ioc::Resolve<int>("someDependency"));
}

TEST_F(ScopeTest, ParentScopeCanBeManuallySetForCreatedScope) {
  auto scope1 = ioc::Resolve<ioc::Scope>("IoC.Scope.Create");
  auto scope2 = ioc::Resolve<ioc::Scope>("IoC.Scope.Create", {scope1});
  ioc::Resolve<CommandPtr>("IoC.Scope.Current.Set", {scope1})->Execute();
  ioc::Resolve<CommandPtr>(
      "IoC.Register",
      {"someDependency", static_cast<ioc::IocFunctor>(
                             [](ioc::ArgsVec args) -> std::any { return 2; })})
      ->Execute();
  ioc::Resolve<CommandPtr>("IoC.Scope.Current.Set", {scope2})->Execute();
  EXPECT_EQ(2, ioc::Resolve<int>("someDependency"));
}
