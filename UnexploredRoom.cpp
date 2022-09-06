#include "pch.h"

UnexploredRoom::UnexploredRoom() {
	this->ID = 0;
	this->distance = 0;
	this->intensity = 0;
	this->weight = 1;
}

UnexploredRoom::UnexploredRoom(UINT64 roomID, int distance, float intensity) {
	this->ID = roomID;
	this->distance = distance;
	this->intensity = intensity;
	this->weight = intensity + (20.0 / (distance + 1.0));
}