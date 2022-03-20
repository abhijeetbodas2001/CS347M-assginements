#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "mmu.h"

int main(void)
{
  void* i = malloc(PGSIZE*10);
  printf(1, "%d\n", i);

  printf(1, "Intial values:\n    Virtual pages = %d\n    Physical pages = %d\n", numvp(), numpp());

  char* addr = mmap(PGSIZE);
  printf(1, "After mmap called:\n    Virtual pages = %d\n    Physical pages = %d\n", numvp(), numpp());

  // Access the newly alloted memory, should result in page fault
  *(addr+PGSIZE) = 1;

  printf(1, "After new memory is accessed:\n    Virtual pages = %d\n    Physical pages = %d\n", numvp(), numpp());
  exit();
}
