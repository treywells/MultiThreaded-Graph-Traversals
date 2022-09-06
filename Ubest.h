#pragma once
struct CompareIntensity {
	bool operator()(UnexploredRoom room1, UnexploredRoom room2) {
		return room1.intensity < room2.intensity;
	}
};

class Ubest : public Ubase {
public:
	void			push(UINT64 roomID, float intensity, int distance);
	UnexploredRoom  pop(void);
	int				size(void) { return U.size(); }
private:
	std::priority_queue<UnexploredRoom, std::vector<UnexploredRoom>, CompareIntensity> U;
};
