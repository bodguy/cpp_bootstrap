#include "heap_alloc.h"
#include <cassert>
#include <cstddef>

void* fmalloc(size_t sz, const char *file, int line) {
  auto* mi = static_cast<malloc_info*>(malloc(sz + sizeof(malloc_info)));
  if (mi == nullptr) {
    return mi;
  }
  mi->file = file;
  mi->line = line;
  mi->next = mi_head;
  if (mi_head != nullptr) {
    mi->next->prev = mi;
  }
  mi->prev = nullptr;
  mi->size = sz;
  mi_head = mi;
  return mi+1;
}

void ffree(void *ptr) {
  if (ptr != nullptr) {
    malloc_info* mi = static_cast<malloc_info*>(ptr) - 1;
    mi->size = ~mi->size;
    if (mi->prev == nullptr) {
      assert(mi_head == mi);
      mi_head = mi->next;
    } else {
      mi->prev->next = mi->next;
    }

    if (mi->next != nullptr) {
      mi->next->prev = mi->prev;
    }
    free(mi);
  }
}

void mprint(const char *reason, malloc_info* mi) {
  printf("%s: %s (%4d): %zd bytes at %p\n", reason, mi->file, mi->line, mi->size, (void*)(mi+1));
}

void dumpmem() {
  malloc_info* mi = mi_head;
  while (mi != nullptr) {
    if (static_cast<ptrdiff_t>(mi->size) >= 0) {
      mprint("LEAKED", mi);
    }
    mi = mi->next;
  }
  mi = mi_head;
   while (mi != nullptr) {
      if (static_cast<ptrdiff_t>(mi->size) < 0) {
        mprint("FREED ", mi);
      }
      mi = mi->next;
   }
}