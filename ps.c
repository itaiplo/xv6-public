#include "types.h"
#include "user.h"
#include "processInfo.h" 

// Manually converts an integer to a string
void itoa(int n, char* s) {
    int i, sign;
    if ((sign = n) < 0)  // Record sign
        n = -n;          // Make n positive
    i = 0;
    do {       // Generate digits in reverse order
        s[i++] = n % 10 + '0';   // Get next digit
    } while ((n /= 10) > 0);     // Delete it
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    // Reverse the string
    int j, k;
    char c;
    for (j = 0, k = i - 1; j < k; j++, k--) {
        c = s[j];
        s[j] = s[k];
        s[k] = c;
    }
}

// Converts process state to a readable string
char* stateToString(int state) {
    switch (state) {
    case 0: return "UNUSED  ";
    case 1: return "EMBRYO  ";
    case 2: return "SLEEPING";
    case 3: return "RUNNABLE";
    case 4: return "RUNNING ";
    case 5: return "ZOMBIE  ";
    default: return "UNKNOWN ";
    }
}

// Pad and print a string with spaces to align columns
void padAndPrintString(char* str, int width) {
    printf(1, "%s", str);
    int len = strlen(str);
    for (int i = len; i < width; i++) {
        printf(1, " ");
    }
}

// Pad and print an integer as a string with spaces to align columns
void padAndPrintInt(int value, int width) {
    char numStr[12]; // Sufficiently large for an int
    itoa(value, numStr);
    padAndPrintString(numStr, width);
}

int main(void) {
    struct processInfo pInfo;
    int totalProcs = getNumProc();
    int maxPid = getMaxPid();

    printf(1, "Total number of active processes: %d\n", totalProcs);
    printf(1, "Maximum PID: %d\n", maxPid);
    printf(1, "PID     STATE     PPID    SZ      NFD   NRSWITCH\n");

    for (int pid = 1; pid <= maxPid; ++pid) {
        if (getProcInfo(pid, &pInfo) == 0) {
            // Print each field with padding for alignment
            padAndPrintInt(pid, 8); // PID
            padAndPrintString(stateToString(pInfo.state), 10); // STATE
            padAndPrintInt(pInfo.ppid, 8); // PPID
            padAndPrintInt(pInfo.sz, 8); // SZ
            padAndPrintInt(pInfo.nfd, 6); // NFD
            padAndPrintInt(pInfo.nrswitch, 10); // NRSWITCH
            printf(1, "\n");
        }
    }

    exit();
}
