#include "pch.h"

void Pipe::writeToPipe(LPVOID buffer, DWORD numOfBytesToWrite, LPDWORD bytesWritten) {
    if (WriteFile(handle, buffer, numOfBytesToWrite, bytesWritten, NULL) == FALSE) {
        printf("Error %d starting CC.exe\n", GetLastError());
        exit(-1);
    }
}

void Pipe::readFromPipe(LPVOID buffer, LPDWORD numOfBytesToRead, LPDWORD bytesRead) {
    if (ReadFile(handle, buffer, *numOfBytesToRead, bytesRead, NULL) == FALSE) {
        printf("Error %d starting CC.exe\n", GetLastError());
        exit(-1);
    }
}

void Pipe::closePipe() {
    if (CloseHandle(handle) == FALSE) {
        printf("Error %d starting CC.exe\n", GetLastError());
        exit(-1);
    }
}