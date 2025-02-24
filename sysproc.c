#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "processInfo.h" 

//my funcs
int getNumProc(void); 
int getMaxPid(void); 
int getProcInfo(int pid, struct processInfo* info); 

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

///////////// our functions//////////////
int
sys_getNumProc(void)
{
    return getNumProc();
}

int
sys_getMaxPid(void)
{
    return getMaxPid();
}

int sys_getProcInfo(void) {
    int processId;                      // Variable to store the process ID argument
    struct processInfo* procDetails;    // Pointer to the processInfo structure argument

    // Retrieve and validate the system call arguments:
    // - The first argument is the process ID.
    // - The second argument is the pointer to a processInfo structure.
    if (argint(0, &processId) < 0 || argptr(1, (void*)&procDetails, sizeof(*procDetails)) < 0)
        return -1;  // Return -1 if there is an issue with the arguments

    // Fetch and return the process information for the given process ID
    return getProcInfo(processId, procDetails);
}


