#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int main(void)
{
  int virt = numvp(), phy = numpp();
  printf(2, "%d\n", virt);
  printf(2, "%d\n", phy);
  exit();
}
