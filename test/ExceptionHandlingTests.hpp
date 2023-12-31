#pragma once
#include <fstream>
#include <memory>
#include <queue>
#include <string>

#include "../include/CommandsQueue.hpp"
#include "../include/ExceptionHandlers.hpp"
#include "../include/MainExceptionHandler.hpp"
#include "Helpers.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class ExceptionHandling : public testing::Test {
 protected:
  void TearDown() override {
    MainExceptionHandler::Reset();
    commands_queue_ = {};
  }
  CommandsQueue commands_queue_;
};

DEFINE_EXCEPTION(MockException);

class MockCommand : public ICommand {
 public:
  void Execute() override { throw MockException(""); }
};

TEST_F(ExceptionHandling, RegisterAndExecuteHandler) {
  bool is_handler_is_called = false;
  auto exception_handler_callback = [&is_handler_is_called](BaseException& e,
                                                            CommandPtr& cmd) {
    is_handler_is_called = true;
    return nullptr;
  };
  CommandPtr cmd = MakeCommand<MockCommand>();
  MockException exp("");
  MainExceptionHandler::RegisterHandler("MockCommand", "MockException",
                                        exception_handler_callback);
  try {
    cmd->Execute();
  } catch (BaseException& e) {
    MainExceptionHandler::Handle(e, cmd);
  }

  EXPECT_TRUE(is_handler_is_called);
}

TEST_F(ExceptionHandling, PushLogCommandToQueueByHandler) {
  MainExceptionHandler::RegisterHandler(
      "MockCommand", "MockException", [&](BaseException& e, CommandPtr& cmd) {
        exception_handlers::PushToQueueFailedCommandLogger(commands_queue_, e);
        return nullptr;
      });

  test_helpers::ClearLogFile();

  commands_queue_.Push(MakeCommand<MockCommand>());
  test_helpers::RunCommands(commands_queue_);

  std::string text = "MockException";
  EXPECT_EQ(text, test_helpers::GetLogFileContent());
}

TEST_F(ExceptionHandling, PushRepeaterCommandToQueue) {
  MainExceptionHandler::RegisterHandler(
      "MockCommand", "MockException", [&](BaseException& e, CommandPtr& cmd) {
        exception_handlers::PushToQueueFailedCommandRepeater(commands_queue_,
                                                             cmd);
        return nullptr;
      });
  auto is_repeater_called = false;
  MainExceptionHandler::RegisterHandler("RepeaterCommand", "MockException",
                                        [&](BaseException& e, CommandPtr& cmd) {
                                          is_repeater_called = true;
                                          return nullptr;
                                        });
  commands_queue_.Push(MakeCommand<MockCommand>());

  test_helpers::RunCommands(commands_queue_);

  EXPECT_TRUE(is_repeater_called);
}

TEST_F(ExceptionHandling, RepeatAndLogCommandOnException) {
  MainExceptionHandler::RegisterHandler(
      "MockCommand", "MockException", [&](BaseException& e, CommandPtr& cmd) {
        exception_handlers::PushToQueueFailedCommandRepeater(commands_queue_,
                                                             cmd);
        return nullptr;
      });
  MainExceptionHandler::RegisterHandler(
      "RepeaterCommand", "MockException",
      [&](BaseException& e, CommandPtr& cmd) {
        exception_handlers::PushToQueueFailedCommandLogger(commands_queue_, e);
        return nullptr;
      });
  test_helpers::ClearLogFile();
  commands_queue_.Push(MakeCommand<MockCommand>());
  test_helpers::RunCommands(commands_queue_);
  EXPECT_EQ(std::string("MockException"), test_helpers::GetLogFileContent());
}

TEST_F(ExceptionHandling, RepeatTwiceAndLogCommandOnException) {
  MainExceptionHandler::RegisterHandler(
      "MockCommand", "MockException", [&](BaseException& e, CommandPtr& cmd) {
        exception_handlers::PushToQueueFailedCommandRepeater(commands_queue_,
                                                             cmd);
        return nullptr;
      });
  MainExceptionHandler::RegisterHandler(
      "RepeaterCommand", "MockException",
      [&](BaseException& e, CommandPtr& cmd) {
        exception_handlers::PushToQueueTwiceFailedCommandRepeater(
            commands_queue_, cmd);
        return nullptr;
      });
  MainExceptionHandler::RegisterHandler(
      "SecondRepeaterCommand", "MockException",
      [&](BaseException& e, CommandPtr& cmd) {
        exception_handlers::PushToQueueFailedCommandLogger(commands_queue_, e);
        return nullptr;
      });

  test_helpers::ClearLogFile();
  commands_queue_.Push(MakeCommand<MockCommand>());
  test_helpers::RunCommands(commands_queue_);
  EXPECT_EQ(std::string("MockException"), test_helpers::GetLogFileContent());
}
