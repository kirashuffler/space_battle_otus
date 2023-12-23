#pragma once

#include "../include/Commands/LogToFileCommand.hpp"
#include "gtest/gtest.h"

TEST(LogToFileCommandTest, LogToFileCommand) {
  std::string filename = "test.txt";
  std::string text = "Hello, World!";

  // Delete or clear the output file if it exists
  std::ofstream ofs;
  ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
  ofs.close();
  LogToFileCommand cmd(filename, text);
  cmd.Execute();

  // Check if the file is correctly written with the provided text
  std::ifstream ifs;
  ifs.open(filename);
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      (std::istreambuf_iterator<char>()));

  EXPECT_EQ(text, content);  // The file should contain the text we wrote
}
