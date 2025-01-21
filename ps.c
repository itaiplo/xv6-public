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

// proccess state to string
char* state_to_str(int state) {
    if (state == 0)
        return "UNUSED  ";
    else if (state == 1)
        return "EMBRYO  ";
    else if (state == 2)
        return "SLEEPING";
    else if (state == 3)
        return "RUNNABLE";
    else if (state == 4)
        return "RUNNING ";
    else if (state == 5)
        return "ZOMBIE  ";
    else
        return "UNKNOWN ";
}


// Pads the provided text with spaces and prints it so that the output occupies a fixed width column.
void pad_and_print_str(char* text, int totalWidth) {
    // Print the original text.
    printf(1, "%s", text);
    
    int textLength = strlen(text);  // Determine the length of the given text
    
    // Print extra spaces until the total printed characters reach totalWidth.
    for (int position = textLength; position < totalWidth; position=position+1) {
        printf(1, " ");
    }
}


// Pads the integer value (converted to a string) with spaces so that the printed output aligns to a fixed column width.
void pad_and_print_int(int val, int colWidth) {
    char numBuffer[12];  // Buffer to hold the string representation of the integer (enough for typical int values)
    itoa(val, numBuffer);    // Convert the integer to a string
    pad_and_print_str(numBuffer, colWidth);  // Print the string with padding to meet the specified width
}


// Main function that displays process information in aligned columns.
int main(void) {
    struct processInfo procDetails;  // Structure to hold details for a specific process
    int activeCount = getNumProc();  // Total number of active processes
    int highestPid = getMaxPid();    // Highest process ID among active processes

    // Print summary information about the processes.
    printf(1, "Total number of active processes: %d\n", activeCount);
    printf(1, "Maximum PID: %d\n", highestPid);
    printf(1, "PID     STATE     PPID    SZ      NFD   NRSWITCH\n");

    // Iterate through all possible process IDs from 1 to highestPid.
    for (int currentPid = 1; currentPid <= highestPid; ++currentPid) {
        // Retrieve process information; if successful, display the details.
        if (getProcInfo(currentPid, &procDetails) == 0) {
            pad_and_print_int(currentPid, 8);                           // Print the process ID with padding
            pad_and_print_str(state_to_str(procDetails.state), 10);    // Print the process state as a string with padding
            pad_and_print_int(procDetails.ppid, 8);                       // Print the parent process ID with padding
            pad_and_print_int(procDetails.sz, 8);                         // Print the size of process memory with padding
            pad_and_print_int(procDetails.nfd, 6);                        // Print the number of file descriptors with padding
            pad_and_print_int(procDetails.nrswitch, 10);                  // Print the number of context switches with padding
            printf(1, "\n");                                          // Move to the next line after printing all fields
        }
    }

    exit();
}

