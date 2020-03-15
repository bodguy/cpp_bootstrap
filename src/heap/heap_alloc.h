#ifndef HEAP_ALLOC_H
#define HEAP_ALLOC_H

#include <cstdlib>
#include <cstdio>

struct malloc_info {
  const char* file;
  int line;
  size_t size;
  malloc_info* next, *prev;
};

static malloc_info* mi_head;

void* fmalloc(size_t sz, const char *file, int line);
void ffree(void *ptr);
void mprint(const char *reason, malloc_info* mi);
void dempmem();

class heap_alloc {
public:
  static void* operator new(std::size_t sz, const char* file = __FILE__, int line = __LINE__) {
    printf("custom new for size %d\n", (int)sz);
    return fmalloc(sz, file, line);
  }

  static void* operator new[](std::size_t sz, const char* file = __FILE__, int line = __LINE__) {
    printf("custom new for size %d\n", (int)sz);
    return fmalloc(sz, file, line);
  }

  static void operator delete(void* ptr, std::size_t sz) {
    printf("custom delete for size %d\n", (int)sz);
    ffree(ptr);
  }

  static void operator delete[](void* ptr, std::size_t sz) {
    printf("custom delete for size %d\n", (int)sz);
    ffree(ptr);
  }
};

#endif
