#pragma once
#include "CommandsQueue.hpp"
#include "Commands/LogCommand.hpp"

namespace exception_handlers {
  void PushToQueueFailedCommandLogger(ICommandsQueue& queue,
                                      BaseException& e){
    queue.Push(std::make_unique<LogCommand>(std::string(e.what())));
  } 
}
