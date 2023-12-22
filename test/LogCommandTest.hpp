#pragma once

#include "../include/Commands/LogCommand.hpp"
#include "gtest/gtest.h"

TEST(LogCommandTest, LogCommand) {
  std::string filename = "logs.txt";
  std::string text = "Hello, World!";

  // Delete or clear the output file if it exists
  std::ofstream ofs;
  ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
  ofs.close();
  LogCommand cmd(text);
  cmd.Execute();

  // Check if the file is correctly written with the provided text
  std::ifstream ifs;
  ifs.open(filename);
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      (std::istreambuf_iterator<char>()));

  EXPECT_EQ(text, content);
}
TEST(LogCommandTest, CheckClassName) {
  LogCommand cmd("");
  std::string class_name = cmd.GetClassName();
  std::string expected_name = "LogCommand";

  EXPECT_EQ(class_name, expected_name);
}
