#ifndef MALLOC_BACKTRACE_H
#define MALLOC_BACKTRACE_H

#include <string>
#include <stdint.h>

#include <iostream>

typedef void *(*MallocHookFunc) (size_t, const void *);

class MallocBacktrace {
 public:
  MallocBacktrace(const std::string &file);
  ~MallocBacktrace();

  static void *MallocHook(size_t size, const void *const_ptr);

 private:
  static void Dump();

  static std::ofstream file_;
  static MallocHookFunc hook_;

  static int64_t malloc_count_;
};

#endif  // MALLOC_BACKTRACE_H
