#include "ExceptionHandlingTests.hpp"
#include "LogCommandTest.hpp"
#include "LogToFileCommandTests.hpp"
#include "MoveTests.hpp"
#include "RotateTests.hpp"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
