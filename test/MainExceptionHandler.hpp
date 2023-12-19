#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../include/MainExceptionHandler.hpp"
#include "../include/Commands/LogCommand.hpp"
#include "../include/CommandsQueue.hpp"
#include "../include/ExceptionHandlers.hpp"

#include <queue>
#include <memory>
#include <fstream>
#include <string>

DEFINE_EXCEPTION(MockException);

class MockCommand : public ICommand {
public:
  void Execute() override {
    throw MockException("");
  }
};

TEST(MainExceptionHandler, BasicRegisterHandlerAndExecuteHandler){
  bool is_handler_is_called = false;
  auto exception_handler_callback = [&is_handler_is_called](BaseException& e, CommandPtr&  cmd){
    is_handler_is_called = true;
    return nullptr;
  };
  CommandPtr cmd = std::make_unique<MockCommand>();
  MockException exp("");
  MainExceptionHandler::RegisterHandler("MockCommand", 
                                        "MockException",
                                        exception_handler_callback);
  try {
    cmd->Execute();
  } catch (BaseException& e) {
    MainExceptionHandler::Handle(e, cmd);
  }

  EXPECT_TRUE(is_handler_is_called);
}


DEFINE_EXCEPTION(MockException1);

class MockCommand1 : public ICommand {
public:
  void Execute() override {
    throw MockException1("");
  }
};

TEST(MainExceptionHandler, PushLogCommandToQueueByHandler){
  CommandsQueue commands_queue;
  commands_queue.Push(std::make_unique<MockCommand1>());

  MainExceptionHandler::RegisterHandler(
      "MockCommand1",
      "MockException1",
      [&](BaseException& e, CommandPtr& cmd){
      exception_handlers::PushToQueueFailedCommandLogger(commands_queue, e);
        return nullptr;
      }
  );
  bool queue_is_empty = false;

  {
    auto cmd = commands_queue.GetCommand();
    try {
      cmd->Execute();
    } catch (BaseException& e) {
      MainExceptionHandler::Handle(e, cmd);
    };
  }

  // try to execute log command, setting up for it

  std::string filename = "logs.txt";
  std::string text = "MockException1";
  std::ofstream ofs;
  ofs.open("logs.txt", std::ofstream::out | std::ofstream::trunc);
  ofs.close();

  // execute LogCommand from queue
  {
    auto cmd = commands_queue.GetCommand();
    cmd->Execute();
  }

  std::ifstream ifs;
  ifs.open(filename);
  std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
  EXPECT_EQ(text, content);
}
