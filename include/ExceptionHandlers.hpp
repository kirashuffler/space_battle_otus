#pragma once
#include "Commands/LogCommand.hpp"
#include "Commands/RepeaterCommand.hpp"
#include "Commands/SecondRepeaterCommand.hpp"
#include "CommandsQueue.hpp"

namespace exception_handlers {
void PushToQueueFailedCommandLogger(ICommandsQueue& queue, BaseException& e) {
  queue.Push(MakeCommand<LogCommand>(std::string(e.what())));
}

void PushToQueueFailedCommandRepeater(ICommandsQueue& queue, CommandPtr& cmd) {
  queue.Push(MakeCommand<RepeaterCommand>(std::move(cmd)));
}

void PushToQueueTwiceFailedCommandRepeater(ICommandsQueue& queue,
                                           CommandPtr& cmd) {
  queue.Push(MakeCommand<SecondRepeaterCommand>(std::move(cmd)));
}

}  // namespace exception_handlers
