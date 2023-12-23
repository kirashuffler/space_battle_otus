#pragma once
#include "LogToFileCommand.hpp"

class LogCommand : public ICommand {
 public:
  LogCommand(const std::string &text) : log_to_file_cmd_{"logs.txt", text} {}
  void Execute() override { log_to_file_cmd_.Execute(); }

 private:
  LogToFileCommand log_to_file_cmd_;
};
