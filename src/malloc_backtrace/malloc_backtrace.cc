#include "malloc_backtrace/malloc_backtrace.h"

#include <execinfo.h>
#include <malloc.h>
#include <stddef.h>

#include <fstream>
#include <iomanip>

std::ofstream MallocBacktrace::file_;
MallocHookFunc MallocBacktrace::hook_;
int64_t MallocBacktrace::malloc_count_;

MallocBacktrace::MallocBacktrace(const std::string &file) {
  MallocBacktrace::file_.open(file.c_str(), std::ios::ate);
  MallocBacktrace::hook_ = __malloc_hook;
  MallocBacktrace::malloc_count_ = 0;

  MallocBacktrace::file_ << "*******************************\n";
  MallocBacktrace::file_ << "* Begin collect malloc:\n";
  MallocBacktrace::file_ << "*******************************\n\n" << std::flush;

  __malloc_hook = MallocBacktrace::MallocHook;
}

MallocBacktrace::~MallocBacktrace() {
  __malloc_hook = MallocBacktrace::hook_;

  MallocBacktrace::file_ << "\n*******************************\n";
  MallocBacktrace::file_ << "* mallc count=" << MallocBacktrace::malloc_count_ << "\n";
  MallocBacktrace::file_ << "*******************************\n" << std::flush;

  MallocBacktrace::file_.close();
}

void *MallocBacktrace::MallocHook(size_t size, const void *const_ptr) {
  void *ptr = NULL;

  // TODO: mutex lock.

  __malloc_hook = MallocBacktrace::hook_;

  ptr = malloc(size);
  MallocBacktrace::Dump();
  ++MallocBacktrace::malloc_count_;

  __malloc_hook = MallocBacktrace::MallocHook;

  return ptr;
}

void MallocBacktrace::Dump() {
  static const size_t kFrameSize = 10;

  void *array[kFrameSize];
  char **strings;

  // get backtrace info
  size_t bt_size = backtrace(array, kFrameSize);
  strings = backtrace_symbols(array, bt_size);

  if (bt_size > 2) {
    for (size_t i = 2; i < bt_size; ++i) {
      MallocBacktrace::file_ << "[" << i << "] " << strings[i] << "\n";
    }
    MallocBacktrace::file_ << "*******************************\n" << std::flush;
  }

  free(strings);
}
