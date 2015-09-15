#include "malloc_backtrace/malloc_backtrace.h"

#include <stdlib.h>

void malloc1() {
  const size_t kMaxSize = 3;

  void *mem_array[kMaxSize] = { NULL };

  for (size_t i = 0; i < kMaxSize; ++i) {
    mem_array[i] = (void *)malloc(10000);
  }
}

void malloc2() {
  const size_t kMaxSize = 2;

  void *mem_array[kMaxSize] = { NULL };

  for (size_t i = 0; i < kMaxSize; ++i) {
    mem_array[i] = (void *)malloc(90000);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    ::printf("error args.\n");
    return 0;
  }

  MallocBacktrace mbt(argv[1]);

  malloc1();
  malloc2();
  malloc1();

  return 0;
}
