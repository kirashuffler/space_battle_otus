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
    BaseException(const char* message)
      : std::runtime_error(message),
        name_(abi::__cxa_demangle(typeid(*this).name(), 0, 0, nullptr))
      {}
    const char* getClassName() const {
        return name_;  // This will give you the mangled name of the class, not a human-readable one.
    }
private:
    const char* name_;
};
