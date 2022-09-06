#pragma once

class Search {
private:
	Ubase* ub;
	Discovered* d;
	UINT64 initialRoomID;
	Pipe* robotPipe;
public:
	Search(Ubase* ub, Discovered* d, UINT64 roomID, Pipe* robotPipe) : ub(ub), d(d), initialRoomID(roomID), robotPipe(robotPipe) {}
	void startSearch();

};
