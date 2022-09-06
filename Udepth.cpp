#include "pch.h"

void Udepth::push(UINT64 roomID, float intensity, int distance) {
	UnexploredRoom room(roomID, distance);
	U.push(room);
}

UnexploredRoom Udepth::pop(void) {
	UnexploredRoom room;
	room = U.top();

	U.pop();
	
	return room;

}