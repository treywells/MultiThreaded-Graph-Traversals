#pragma once

class UnexploredRoom {
public:
	UINT64 ID;
	int    distance;
	float intensity;
	float weight;
	UnexploredRoom();
	UnexploredRoom(UINT64 roomID, int distance, float intensity = 0);
};
