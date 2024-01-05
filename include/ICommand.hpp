#pragma once
#include <cxxabi.h>  // for __cxa_demangle

#include <memory>

#include "BaseException.hpp"
#include "demangle.hpp"

struct ICommand {
  const char* GetClassName() const {
    /* return (abi::__cxa_demangle(typeid(*this).name(), 0, 0, nullptr)); */
    return demangle(typeid(*this).name());
  };
  virtual void Execute(){};
  virtual ~ICommand() = default;
};

using CommandPtr = std::shared_ptr<ICommand>;

template <class T, class... Args>
CommandPtr MakeCommand(Args&&... args) {
  return CommandPtr(std::make_shared<T>(std::forward<Args>(args)...));
}
