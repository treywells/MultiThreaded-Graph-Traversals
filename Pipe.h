#pragma once

class Pipe {
public:
	HANDLE handle;
	Pipe(HANDLE handle) : handle(handle) {}
	void writeToPipe(LPVOID buffer, DWORD numOfBytesToWrite, LPDWORD bytesWritten);
	void readFromPipe(LPVOID buffer, LPDWORD numOfBytesToRead, LPDWORD bytesRead);
	void closePipe();
};
