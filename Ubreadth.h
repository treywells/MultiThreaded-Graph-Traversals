#pragma once

class Ubreadth : public Ubase {
public:
	void			push(UINT64 roomID, float intensity, int distance);
	UnexploredRoom  pop(void);
	int				size(void);

private:
	std::queue<UnexploredRoom> U;
};
