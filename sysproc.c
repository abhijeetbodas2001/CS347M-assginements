#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_numvp(void) {
    // Round up the size in bytes to nearest multiple of PGSIZE,
    // then return the number of pages
    return PGROUNDUP(myproc()->sz)/PGSIZE;
}

int sys_numpp(void) {
    pde_t* pgdir = myproc()->pgdir;
    int num_pp = 0;   // counter for number of physical pages
    pte_t* pte;

    for (uint i = 0; i < KERNBASE; i = i + PGSIZE) {
      pte = walkpgdir(pgdir, (int *)i, 0);
      if (pte) {  // Physical address is valid
        if (*pte & PTE_P) { // Page is present
          num_pp++;
        }
      }
    }

    return num_pp;
}


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_mmap(void) {
  int addr = myproc()->sz;

  // Number of bytes
  int n;
  argint(0, &n);  // Store the syscall argument in n

  // Handle invalid aguments
  if (n < 0 || n%PGSIZE != 0) {
    return 0;
  }

  myproc()->sz = myproc()->sz + n;

  return addr;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
