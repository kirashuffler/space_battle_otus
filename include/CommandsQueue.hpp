#pragma once
#include "ICommand.hpp"
#include <queue>
#include <memory>
#include "BaseException.hpp"
#include <iostream>

DEFINE_EXCEPTION(CommandsQueueEmptyException)

class CommandsQueue {
public:
  void Push(std::unique_ptr<ICommand> cmd){
    commands_queue_.emplace(std::move(cmd));
  }
  CommandPtr GetCommand() {
    if (commands_queue_.size() == 0)
      throw CommandsQueueEmptyException("");
    CommandPtr cur_cmd = std::move(commands_queue_.front());
    commands_queue_.pop();
    return cur_cmd;
  }

  size_t Size() {
    return commands_queue_.size();
  }

private:
  std::queue<std::unique_ptr<ICommand>> commands_queue_;
};
