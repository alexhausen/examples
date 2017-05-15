#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

/*
 window2> serial.exe client \\.\CNCA0
 window1> serial.exe server \\.\CNCB0
*/

void exit_error(const char* msg) {
    puts(msg);
    exit(1);
}

void usage_error(const char* msg) {
    if (msg) puts(msg);
    exit_error("Usage: serial.exe [client|server] [COMPORT]");
}

HANDLE serial_open(const char* port) {
    HANDLE hSerial = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        exit_error("ERROR: open serial port error");
    }
    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    if (!GetCommState(hSerial, &dcb)) {
        exit_error("ERROR: get serial port state");
    }
    dcb.BaudRate = CBR_9600;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    if (!SetCommState(hSerial, &dcb)) {
        exit_error("ERROR: set serial port state");
    }
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        exit_error("ERROR: set communication timeout");
    }
    printf("%s opened\n", port); 
    return hSerial;
}

void serial_close(HANDLE h) {
  CloseHandle(h);
}

unsigned serial_read(HANDLE h, char* buffer, unsigned max_capacity) {
    DWORD total_read = 0;
    if (!ReadFile(h, buffer, max_capacity, &total_read, NULL)) {
        return 0;
    }
    return total_read;
}

unsigned serial_write(HANDLE h, const char* buffer, unsigned buffer_size) {
    DWORD total_written = 0;
    if (!WriteFile(h, buffer, buffer_size, &total_written, NULL)) {
        return 0;
    }
    return total_written;
}

void client(const char* port) {
    HANDLE h = serial_open(port);
    bool quit = false;
    while (!quit) {
        printf("> ");
        char buffer[512];
        scanf("%511s", buffer);
        unsigned buffer_size = strlen(buffer) + 1;
        unsigned n = serial_write(h, buffer, buffer_size);
        if (n != buffer_size) {
            printf("write: %u != %u\n", buffer_size, n);
        }
        quit = strcmp(buffer, "quit") == 0;
    }
    serial_close(h);
}

bool quit_server = false;

DWORD WINAPI server_thread(LPVOID param) { 
    const char* port = (const char*) param;
    HANDLE h = serial_open(port);
    while (!quit_server) {
        char buffer[513];
        unsigned n = serial_read(h, buffer, 512);
        if (n == 0) continue; // timeout
        printf("server: received '%s'\n", buffer);
        quit_server = strcmp(buffer, "quit") == 0;
    }
    serial_close(h);
    return 0;
}

void server(const char* port) {
    DWORD thread_id;
    HANDLE h = CreateThread( 
        NULL,                // default security attributes
        0,                   // use default stack size  
        server_thread,       // thread function name
        (LPVOID)port,        // argument to thread function 
        0,                   // use default creation flags 
        &thread_id);         // returns the thread identifier
    if (h == NULL) {
        exit_error("Thread creation error");
    }
    while (!quit_server) {
        // puts("do stuff");
    }
    WaitForSingleObject(h, INFINITE);
    CloseHandle(h);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        usage_error("Wrong number of parameters");
    }
    if (strcmp(argv[1], "client") == 0) {
        client(argv[2]);
    } else if (strcmp(argv[1], "server") ==0) {
        server(argv[2]);
    } else {
        usage_error("wrong parameter 1: client|server");
    }
    return 0;
}