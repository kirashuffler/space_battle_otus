#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include "ICommand.hpp"
#include "BaseException.hpp"

class MainExceptionHandler {
  using ExceptionType = std::string;
  using CommandType = std::string;
  using ExceptionHandlerCb = std::function<std::unique_ptr<ICommand>(BaseExeption&, ICommand*)>;
public:
  static std::unique_ptr<ICommand> Handle(BaseExeption& e, ICommand* cmd){
    auto exception_name = e.GetClassName();
    auto cmd_name = cmd->GetClassName();
    return store_[cmd_name][exception_name](e, cmd);
  }

  static void RegisterHandler(CommandType cmd_name, ExceptionType exception_name, ExceptionHandlerCb handler) {
    store_[cmd_name][exception_name] = handler;
  };
private:
  static std::unordered_map<CommandType, std::unordered_map<ExceptionType, ExceptionHandlerCb>> store_ {};
};
