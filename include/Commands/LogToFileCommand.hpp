#pragma once
#include <fstream>
#include <string>

#include "../BaseException.hpp"
#include "../ICommand.hpp"

DEFINE_EXCEPTION(LogToFileCommandUnableToOpenFileException)

class LogToFileCommand : public ICommand {
 public:
  LogToFileCommand(const std::string &filename, const std::string &text)
      : filename_(filename), text_(text) {}

  void Execute() override {
    std::ofstream file;
    file.open(filename_);
    if (file.is_open()) {
      file << text_;
      file.close();
    } else {
      throw LogToFileCommandUnableToOpenFileException("");
    }
  }

 private:
  std::string filename_;
  std::string text_;
};
