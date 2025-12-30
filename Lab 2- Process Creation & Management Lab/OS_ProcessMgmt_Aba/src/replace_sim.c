#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Run "cmd /c dir" as the child process
    char command[] = "cmd /c dir";

    printf("Parent PID: %lu\n", GetCurrentProcessId());

    if (!CreateProcess(
        NULL,          // Application name (NULL since we pass command line)
        command,       // Command line
        NULL, NULL,    // Process/thread security attributes
        FALSE,         // Inherit handles
        0,             // Creation flags
        NULL, NULL,    // Environment + current directory
        &si, &pi))     // Startup & process info
    {
        printf("CreateProcess failed. Error: %lu\n", GetLastError());
        return 1;
    }

    // Wait until child finishes
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get child's exit code
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    printf("Child exited with code %lu\n", exitCode);

    // Clean up
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Exit with same code as child (simulate exec)
    return exitCode;
}