#pragma once
#include "../ICommand.hpp"

class RepeaterCommand : public ICommand {
public:
  RepeaterCommand(CommandPtr cmd) : cmd_ { std::move(cmd) }{}
  void Execute() override {
    cmd_->Execute();
  }
private:
  CommandPtr cmd_;
};
