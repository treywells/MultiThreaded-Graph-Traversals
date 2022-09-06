// Homework1Part1.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
    Corbin (Trey) Wells
    CSCE 313 - 200
    Spring 2022
*/

#include "pch.h"

int main(int argc, char** argv)
{

    auto startTime = std::chrono::high_resolution_clock::now();

    // Check if right number of command line args
    if (argc != 4) {
        printf("Not enough commandline args\n");
        exit(-1);
    }

    // Connect to the CC
    PROCESS_INFORMATION pi;
    STARTUPINFO s;
    GetStartupInfo(&s);
    char path[] = "CC.exe";
    if (CreateProcess(path, NULL, NULL, NULL,
        false, 0, NULL, NULL, &s, &pi) == FALSE)
    {
        printf("Error % d starting % s\n", GetLastError(), path);
        exit(-1);
    }

    // PID for the CC
    int PID = pi.dwProcessId;

    // Pipename for the CC
    char buffer[50];
    sprintf(buffer, "\\\\.\\pipe\\CC-%X", PID);

    // wait for the CC to initialize the pipe from its end
    while (WaitNamedPipe(buffer, INFINITE) == FALSE)
        Sleep(100); // pause for 100 ms

    // now open the pipe
    HANDLE CC = CreateFile(buffer, GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    // Create the pipe object for the CC
    Pipe CCPipe(CC);

    // Send initial command to CC to say cave, planet, and number of robots
    CommandCC firstCommand{};
    firstCommand.command = CONNECT;
    firstCommand.planet = (UCHAR) atoi(argv[1]);
    firstCommand.cave = (DWORD) atoi(argv[2]);
    firstCommand.robots = 1;

    printf("Connecting to CC with planet %d, cave %d, robots %d...\n", firstCommand.planet, firstCommand.cave, firstCommand.robots);

    // Connect to the CC
    CCPipe.writeToPipe(&firstCommand, sizeof(firstCommand), NULL);

    ResponseCC response;
    DWORD sizeOfResponse = sizeof(response);


    // Get the response of the CC to the initial connection
    CCPipe.readFromPipe(&response, &sizeOfResponse, NULL);

    printf("CC says: status = %d, msg = '%s'\n",response.status, response.msg);

    // Check if CC terminates and exit system
    if (response.status == FAILURE) {
        printf("Connection error, quitting...\n");
        exit(-1);
    }

    // Create the pipename for the one robot
    char robotPipeName[1024];
    int k = 0;
    sprintf(robotPipeName, "\\\\.\\pipe\\CC-%X-robot-%X", PID, k);

    while (WaitNamedPipe(robotPipeName, INFINITE) == FALSE)
        Sleep(100);

    // Open the pipe for the robot
    HANDLE ROBOT = CreateFile(robotPipeName, GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    // Create pipe object for ROBOT
    Pipe robotPipe(ROBOT);

    CommandRobot robotConnect;
    robotConnect.command = CONNECT;
    robotConnect.room = NULL;

    printf("Connecting to robot %d...\n", k);

    
    robotPipe.writeToPipe(&robotConnect, sizeof(robotConnect), NULL);


    ResponseRobot responseToConnect;
    DWORD sizeOfResponseRobot = sizeof(responseToConnect);

    // Read in response from robot to the initial connection
    robotPipe.readFromPipe(&responseToConnect, &sizeOfResponseRobot, NULL);

    printf("Robot says: status = %d, msg = '%s'\n", responseToConnect.status, responseToConnect.msg);

    // Check if robot fails to connect and exit system
    if (response.status == FAILURE) {
        printf("Connection error, quitting...\n");
        exit(-1);
    }

    NodeTuple64 initialRoom;
    DWORD sizeOfRoom = sizeof(initialRoom);

    robotPipe.readFromPipe(&initialRoom, &sizeOfRoom, NULL);

    printf("Current position: room %I64X, light intensity %.2f\n", initialRoom.node, initialRoom.intensity);

    // ------------------------------------------------------- //
    // ------------------------------------------------------- //
    // ------------------------------------------------------- //
    
    // This is where we start the search from
    Ubase* ub{};
    Discovered* d = new Discovered();
    UINT64 initialRoomID = initialRoom.node;

    // Determine which search to use
    std::string searchInput = argv[3];

    if (searchInput == "BFS") {
        ub = new Ubreadth;
    }
    else if (searchInput == "DFS") {
        ub = new Udepth;
    }
    else if (searchInput == "bFS") {
        ub = new Ubest;
    }
    else if (searchInput == "A*") {
        ub = new Astar;
    }
    else {
        printf("Invalid serach algorithm argument\n");
        exit(-1);
    }

    // Construct the search class
    Search newSearch(ub, d, initialRoomID, &robotPipe);

    // Start the search
    printf("Starting search using %s...\n", searchInput.c_str());
    newSearch.startSearch();


    // Start Disconnecting
    printf("-------------------\n");

    // Disconnect from robot
    printf("Disconnecting robot 0...\n");

    CommandRobot robotDisconnect{};
    robotDisconnect.command = DISCONNECT;
    robotDisconnect.room = 100;

    // Send command to tell robot to disconnect
    if (WriteFile(ROBOT, &robotDisconnect, sizeof(robotDisconnect), NULL, NULL) == FALSE) {
        printf("Error %d starting %s\n", GetLastError(), path);
        exit(-1);
    }

    // Close the robot's pipe
    robotPipe.closePipe();

    CommandCC disconnectCC{};
    disconnectCC.cave = NULL;
    disconnectCC.command = DISCONNECT;
    disconnectCC.planet = NULL;
    disconnectCC.robots = NULL;

    // Disconnect from CC
    printf("Disconnecting CC...\n");

    // Send command to tell CC to disconnect
    CCPipe.writeToPipe(&disconnectCC, sizeof(disconnectCC), NULL);

    // Close the CC's pipe
    CCPipe.closePipe();

    printf("Waiting for CC.exe to quit\n");

    DWORD waitReturn = WaitForSingleObject(pi.hProcess, INFINITE);

    auto endTime = std::chrono::high_resolution_clock::now();

    // Calculate execution time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    printf("Execution time %.2f seconds\n",(float) duration.count() / 1000.0);


}
