#pragma once
#include <fstream>
#include <memory>
#include <queue>
#include <string>

#include "../include/CommandsQueue.hpp"
#include "../include/MainExceptionHandler.hpp"

namespace test_helpers {

void ClearLogFile() {
  std::ofstream ofs;
  ofs.open("logs.txt", std::ofstream::out | std::ofstream::trunc);
  ofs.close();
}

std::string GetLogFileContent() {
  std::ifstream ifs;
  ifs.open("logs.txt");
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      (std::istreambuf_iterator<char>()));
  return content;
}

void RunCommands(ICommandsQueue& queue) {
  while (queue.Size() > 0) {
    auto cmd = queue.GetCommand();
    try {
      cmd->Execute();
    } catch (BaseException& e) {
      MainExceptionHandler::Handle(e, cmd);
    }
  }
}

}  // namespace test_helpers
