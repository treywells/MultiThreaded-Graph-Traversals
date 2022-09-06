#include "pch.h"

void Ubreadth::push(UINT64 roomID, float intensity, int distance) {
	UnexploredRoom newRoom(roomID, distance);

	U.push(newRoom);
}

UnexploredRoom Ubreadth::pop(void) {
	// We must store the front of queue in a variable
	// then pop the front of the queue then return the stored front
	UnexploredRoom newRoom;
	newRoom = U.front();
	U.pop();
	return newRoom;
}

int Ubreadth::size(void) {
	return U.size();
}

