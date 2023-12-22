#pragma once
#include "../ICommand.hpp"
#include "../BaseException.hpp"

DEFINE_EXCEPTION(SecondRepeaterCommandWrongCommandForRepeatingException);

class SecondRepeaterCommand : public ICommand {
public:
  SecondRepeaterCommand(CommandPtr cmd) : cmd_ { std::move(cmd) }{
    if (cmd_->GetClassName() != std::string("RepeaterCommand"))
      throw SecondRepeaterCommandWrongCommandForRepeatingException(""); 
  }
  void Execute() override {
    cmd_->Execute();
  }
private:
  CommandPtr cmd_;
};
