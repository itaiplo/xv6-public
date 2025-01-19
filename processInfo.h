#ifndef _PROCESSINFO_H
#define _PROCESSINFO_H

// processInfo.h
struct processInfo {
    int state; // process state
    int ppid; // parent PID
    int sz; // size of process memory, in bytes
    int nfd; // number of open file descriptors
    int nrswitch; // number of context switches
};

#endif // _PROCESSINFO_H