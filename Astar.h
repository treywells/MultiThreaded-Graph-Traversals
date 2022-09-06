#pragma once

struct CompareWeight {
	bool operator()(UnexploredRoom room1, UnexploredRoom room2) {
		return room1.weight < room2.weight;
	}
};

class Astar : public Ubase {
public:
	void			push(UINT64 roomID, float intensity, int distance);
	UnexploredRoom  pop(void);
	int				size(void) { return U.size(); }
private:
	std::priority_queue<UnexploredRoom, std::vector<UnexploredRoom>, CompareWeight> U;
};