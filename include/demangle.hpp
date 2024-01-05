#pragma once
#include <cxxabi.h>

#include <string_view>

const char* demangle(std::string_view str) {
  return abi::__cxa_demangle(str.data(), 0, 0, nullptr);
}
