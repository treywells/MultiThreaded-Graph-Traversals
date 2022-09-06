#include "pch.h"

void Astar::push(UINT64 roomID, float intensity, int distance) {
	UnexploredRoom room(roomID, distance, intensity);
	U.push(room);
}

UnexploredRoom Astar::pop(void) {
	UnexploredRoom room = U.top();
	U.pop();
	return room;
}