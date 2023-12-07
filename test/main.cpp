#include "gtest/gtest.h"
#include "MoveTests.hpp"
#include "RotateTests.hpp"
#include "LogToFileCommandTests.hpp"
#include "LogCommandTest.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
