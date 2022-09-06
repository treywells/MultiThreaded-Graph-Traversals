#include "pch.h"

void Search::startSearch() {

	// Stores the robots response to searching the initial room
	DWORD bufferSize = 68;
	char* buff;
	buff = (char*)malloc(bufferSize);
	DWORD bytesRead;

	// Keeps track of the current step for the search
	int currentStep = 0;

	// Add the initial starting room to the U and D sets
	ub->push(initialRoomID, 0, 0);
	d->CheckAdd(initialRoomID);

	// Keep running algorithm until all rooms have been explored
	// If this while loop naturally ends, there is no exit to the cave system
	while (ub->size() != 0) {
		currentStep++;

		UnexploredRoom nextRoomToVisit = ub->pop();
		
		// Make command to visit nextRoomToVisit
		CommandRobot visitNextRoom{};
		visitNextRoom.command = MOVE;
		visitNextRoom.room = nextRoomToVisit.ID;

		// Send move command to flybot
		robotPipe->writeToPipe(&visitNextRoom, sizeof(visitNextRoom), NULL);

		// Read the response from the flybot
		robotPipe->readFromPipe(buff, &bufferSize, &bytesRead);

		// Checks to see if buffer needs to be resized
		if (bytesRead >= bufferSize) {
			// Stores the amount of bytes still in the buffer of the pipe
			DWORD bytesStillInPipe;
			if (PeekNamedPipe(robotPipe->handle, NULL, NULL, NULL, &bytesStillInPipe, NULL) == FALSE) {
				printf("Error %d starting CC.exe\n", GetLastError());
				exit(-1);
			}

			if (bytesStillInPipe != 0) {
				size_t newBufferSize = ((size_t)(bufferSize) + (size_t)bytesStillInPipe);

				// Possible memory leak!!!
				// Reallocate the buffer to be able to contain the whole read file
				char* newBuff = (char*) realloc((char*)buff, newBufferSize);

				// Make sure the reallocation succeeds, else exit the program
				if (newBuff == nullptr) {
					printf("Memory allocation failure, exiting...\n");
					exit(-1);
				}

				buff = (char*)newBuff;
				newBuff = nullptr;


				// Read in the rest of the pipe
				robotPipe->readFromPipe(buff + bufferSize, &bytesStillInPipe, NULL);

				bytesRead = bufferSize + bytesStillInPipe;
				bufferSize = newBufferSize;

			}

		}

		ResponseRobot* robotResponse;
		robotResponse = (ResponseRobot*)buff;

		// Check if NULL pointer
		if (robotResponse == NULL) {
			exit(-1);
		}

		// Check status of flybot
		if (robotResponse->status == 0) {
			printf("Robot failed, msg = %s", robotResponse->msg);
			exit(-1);
		}

		// Stores all neighboring rooms
		NodeTuple64* neighbors;
		neighbors = (NodeTuple64*)(buff + sizeof(ResponseRobot));

		int degree = (bytesRead - sizeof(ResponseRobot)) / sizeof(NodeTuple64);
		
		// If there are no neighbors, you found the exit!
		if (degree == 0) {
			printf("Found exit %llX, %d steps, distance %d\n",nextRoomToVisit.ID, currentStep, nextRoomToVisit.distance);
			free(buff);
			return;
		}

		for (int i = 0; i < degree; i++) {
			if (d->CheckAdd(neighbors[i].node)) {
				ub->push(neighbors[i].node, neighbors[i].intensity, nextRoomToVisit.distance + 1);
			}
		}

		// Printout for that room search
		printf("%d) visiting %llX, degree %d, discovered %d\n", currentStep, nextRoomToVisit.ID, degree, d->size());

	}

	printf("No exit found\n");
	free(buff);



}
