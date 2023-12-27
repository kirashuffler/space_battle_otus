#pragma once
#include <vector>

#include "../ICommand.hpp"

class MacroCommand : public ICommand {
 public:
  MacroCommand(std::vector<CommandPtr> commands)
      : commands_{std::move(commands)} {}
  void Execute() {
    for (auto &&cmd : commands_) {
      cmd->Execute();
    }
  }

 private:
  std::vector<CommandPtr> commands_;
};
