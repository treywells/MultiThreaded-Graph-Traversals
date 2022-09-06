#pragma once

class Udepth : public Ubase {
public:
	void			push(UINT64 roomID, float intensity, int distance);
	UnexploredRoom  pop(void);
	int				size(void) { return U.size(); }
private:
	std::stack<UnexploredRoom> U;
};