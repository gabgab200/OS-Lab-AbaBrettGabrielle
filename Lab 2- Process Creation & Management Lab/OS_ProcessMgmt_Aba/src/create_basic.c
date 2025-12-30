#include <stdio.h>
#include <windows.h>

int main() {
    printf("Parent PID: %lu\n", GetCurrentProcessId());

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char cmd[100];
    sprintf(cmd, "child_echo.exe %lu", GetCurrentProcessId());

    if (CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        printf("Child exited with code: %lu\n", exitCode);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        printf("Failed to create child process.\n");
    }

    return 0;
}