#include "types.h"
#include "user.h"
#include "processInfo.h" 

// Helper function to reverse a string in place.
void reverse(char* str) {
    int start = 0;
    int end = strlen(str) - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Converts an integer n to a string and stores it in s.
void itoa(int n, char* s) {
    int i = 0;

    // Handle negative numbers by converting n to positive.
    if (n < 0)
        n = -n;

    // Generate digits in reverse order.
    do {
        s[i++] = (n % 10) + '0';
        n /= 10;
    } while (n > 0);


    s[i] = '\0';  // Null-terminate the string

    // Reverse the string to obtain the correct order.
    reverse(s);
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
