#include "pch.h"

void Ubest::push(UINT64 roomID, float intensity, int distance) {
	UnexploredRoom room(roomID, distance, intensity);
	U.push(room);
}

UnexploredRoom Ubest::pop(void) {
	UnexploredRoom room = U.top();
	U.pop();
	return room;
}
