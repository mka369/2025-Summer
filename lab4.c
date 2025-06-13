#define _DEFAULT_SOURCE
#define _ISOC99_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[64];
  ssize_t len = snprintf(buf, 64, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                       : *(void **)data);
  if (len < 0) {
    perror("snprintf");
    exit(EXIT_FAILURE);
  }
  write(STDOUT_FILENO, buf, len);
}

void print_block(char *start) {
  for (int i = 0; i < (128 - sizeof(struct header)); i++) {
    char *addr = (start + sizeof(struct header) + i);
    uint64_t val = (uint64_t)*addr;
    print_out("%lu\n", &val, sizeof(val));
  }
}

int main(void) {
  void *heap_start = sbrk(0);
  if (sbrk(156) == (void *)-1) {
    perror("sbrk");
    exit(EXIT_FAILURE);
  }

  struct header *block1 = (struct header *)heap_start;
  struct header *block2 = (struct header *)(heap_start + 128);

  block1->size = 128;
  block1->next = NULL; // block1 <- block2, not block1 -> block2! WHY?
  block2->size = 128;
  block2->next = block1;

  /**
  int *ptr1 = block1 + sizeof(struct header);
  for (int i=0; i<(128 - sizeof(struct header)); i++) {
    *ptr1 = 0;
    ptr1 += 4;
  }

  int *ptr2 = block2 + sizeof(struct header);
  for (int i=0; i<(128 - sizeof(struct header)); i++) {
    *ptr2 = 1;
    ptr2 += 4;
  }
  **/

  memset(block1 + 1, 0, 128 - sizeof(struct header));
  memset(block2 + 1, 1, 128 - sizeof(struct header));

  print_out("first block: %p\n", &block1, sizeof(block1));
  print_out("second block: %p\n", &block2, sizeof(block2));
  print_out("first block size: %lu\n", &block1->size, sizeof(block1->size));
  print_out("first block next: %p\n", &block1->next, sizeof(block1->next));
  print_out("second block size: %lu\n", &block2->size, sizeof(block2->size));
  print_out("second block next: %p\n", &block2->next, sizeof(block2->next));
  print_block((char *)block1);
  print_block((char *)block2);

  return 0;
}
