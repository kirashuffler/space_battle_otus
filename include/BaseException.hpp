#pragma once
#include <stdexcept>
#include <string>
#include <cxxabi.h>  // for __cxa_demangle

#define DEFINE_EXCEPTION(name) \
class name : public BaseException { \
public: \
    explicit name(const char* what_arg) : BaseException(what_arg) {} \
};

class BaseException : public std::runtime_error {
public:
  BaseException(const char* extra_info)
    : std::runtime_error(""),
    extra_info_ { extra_info }
    {}
  const char* what() const noexcept override {
    return (abi::__cxa_demangle(typeid(*this).name(), 0, 0, nullptr));
  }
  std::string GetExtraInfo() const {
    return extra_info_;
  }
private:
    std::string extra_info_;
};
