#pragma once
#include <iostream>
#include <memory>
#include <queue>

#include "BaseException.hpp"
#include "ICommand.hpp"

DEFINE_EXCEPTION(CommandsQueueEmptyException);

class ICommandsQueue {
 public:
  virtual void Push(CommandPtr cmd) = 0;
  virtual CommandPtr GetCommand() = 0;
  virtual size_t Size() = 0;
  virtual ~ICommandsQueue() = default;
};

class CommandsQueue : public ICommandsQueue {
 public:
  void Push(CommandPtr cmd) override {
    commands_queue_.emplace(std::move(cmd));
  }
  CommandPtr GetCommand() override {
    if (commands_queue_.size() == 0) throw CommandsQueueEmptyException("");
    CommandPtr cur_cmd = std::move(commands_queue_.front());
    commands_queue_.pop();
    return cur_cmd;
  }

  size_t Size() override { return commands_queue_.size(); }

 private:
  std::queue<CommandPtr> commands_queue_;
};
