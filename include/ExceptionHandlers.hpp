#pragma once
#include "CommandsQueue.hpp"
#include "Commands/LogCommand.hpp"
#include "Commands/RepeaterCommand.hpp"
#include "Commands/SecondRepeaterCommand.hpp"

namespace exception_handlers {
  void PushToQueueFailedCommandLogger(ICommandsQueue& queue,
                                      BaseException& e){
    queue.Push(std::make_unique<LogCommand>(std::string(e.what())));
  } 

  void PushToQueueFailedCommandRepeater(ICommandsQueue& queue,
      CommandPtr& cmd){   
    queue.Push(std::make_unique<RepeaterCommand>(std::move(cmd)));
  }

  void PushToQueueTwiceFailedCommandRepeater(ICommandsQueue& queue,
      CommandPtr& cmd){   
    queue.Push(std::make_unique<SecondRepeaterCommand>(std::move(cmd)));
  }

}
