#pragma once
#include <cxxabi.h>  // for __cxa_demangle

struct ICommand {
  const char* GetClassName() const {
    return (abi::__cxa_demangle(typeid(*this).name(), 0, 0, nullptr));
  };
  virtual void Execute() {};
  virtual ~ICommand() = default;
};
