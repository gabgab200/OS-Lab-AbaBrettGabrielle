#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    DWORD pid = GetCurrentProcessId();
    printf("Child process started! PID = %lu\n", pid);

    // Stay alive for 10 seconds
    Sleep(60000);

    printf("Child process exiting...\n");
    return 0;
}