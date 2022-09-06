#pragma once

class Discovered {
private:
	std::set<UINT64> D;
public:
	bool CheckAdd(UINT64 roomID);
	int size() { return D.size(); }
};
