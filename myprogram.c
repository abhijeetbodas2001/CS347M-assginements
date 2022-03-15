#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "mmu.h"

int main(void)
{
  void* i = malloc(PGSIZE*10);
  printf(1, "%d\n", i);

  int virt = numvp(), phy = numpp();
  printf(2, "%d\n", virt);
  printf(2, "%d\n", phy);
  exit();
}
