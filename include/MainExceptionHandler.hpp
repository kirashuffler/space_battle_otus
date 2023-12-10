#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include "ICommand.hpp"
#include "BaseException.hpp"
#include <iostream>

DEFINE_EXCEPTION(MainExceptionHandlerNoSuchHandlerCallbackException)
DEFINE_EXCEPTION(MainExceptionHandlerNullptrCommandObjException)

class MainExceptionHandler {
public:
  using ExceptionType = std::string;
  using CommandType = std::string;
  using ExceptionHandlerCb = std::function<CommandPtr(BaseException&, CommandPtr&)>;
  using HandlersMap = std::unordered_map<CommandType, std::unordered_map<ExceptionType, ExceptionHandlerCb>>; 
public:
  static CommandPtr Handle(BaseException& e, CommandPtr& cmd){
    auto exception_name = e.what();
    if (!cmd.get())
      throw MainExceptionHandlerNullptrCommandObjException("");
    auto cmd_name = cmd->GetClassName();
    try {
      return store_[cmd_name][exception_name](e, cmd);
    } catch (std::exception& e) {
      throw MainExceptionHandlerNoSuchHandlerCallbackException(e.what());
    }
  }

  static void RegisterHandler(CommandType cmd_name, ExceptionType exception_name, ExceptionHandlerCb handler) {
    store_[cmd_name][exception_name] = handler;
  }
private:
  static HandlersMap store_;
};

MainExceptionHandler::HandlersMap MainExceptionHandler::store_ = {};
