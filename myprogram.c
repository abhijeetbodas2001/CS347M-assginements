#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "mmu.h"

int main(void)
{
  void* i = malloc(PGSIZE*10);
  printf(1, "%d\n", i);

  printf(2, "Initial virtual pages: %d\n", numvp());
  printf(2, "Initial physical pages: %d\n", numpp());

  char* addr = mmap(PGSIZE);
  printf(1, "Pages added after: %d\n", addr);

  printf(2, "Final virtual pages: %d\n", numvp());
  printf(2, "Final physical pages: %d\n", numpp());

  // Access the newly alloted memory, should result in page fault
  printf(1, "%d", *(addr+PGSIZE));
  exit();
}
