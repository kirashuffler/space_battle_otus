#include "gtest/gtest.h"
#include "MoveTests.hpp"
#include "RotateTests.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
