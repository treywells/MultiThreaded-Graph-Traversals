#include "pch.h"

bool Discovered::CheckAdd(UINT64 roomID) {
	
	return (D.insert(roomID).second);
}