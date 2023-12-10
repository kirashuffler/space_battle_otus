#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <utility>

#include "../include/MainExceptionHandler.hpp"

DEFINE_EXCEPTION(MockException);

class MockCommand : public ICommand {
public:
  void Execute() override {
    throw MockException("");
  }
};

TEST(MainExceptionHandler, RegisterHandlerAndExecuteHandler){
  bool is_handler_is_called = false;
  auto exception_handler = [&is_handler_is_called](BaseException& e, ICommand* cmd){
    is_handler_is_called = true;
    return nullptr;
  };
  MockCommand cmd;
  MockException exp("");
  MainExceptionHandler::RegisterHandler(cmd.GetClassName(), 
                                        exp.GetClassName(),
                                        exception_handler);
  try {
    cmd.Execute();
  } catch (BaseException& e) {
    MainExceptionHandler::Handle(e, &cmd);
  }

  EXPECT_TRUE(is_handler_is_called);
}
