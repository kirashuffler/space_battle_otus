#pragma once
#include "CommandsQueue.hpp"
#include "Commands/LogCommand.hpp"
#include "Commands/RepeaterCommand.hpp"

namespace exception_handlers {
  void PushToQueueFailedCommandLogger(ICommandsQueue& queue,
                                      BaseException& e){
    queue.Push(std::make_unique<LogCommand>(std::string(e.what())));
  } 

  void PushToQueueFailedCommandRepeater(ICommandsQueue& queue,
      CommandPtr& cmd){   
    queue.Push(std::make_unique<RepeaterCommand>(std::move(cmd)));
  }
}
