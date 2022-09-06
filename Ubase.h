#pragma once
class Ubase {
public:
	virtual void			push(UINT64 roomID, float intensity, int distance) = 0;
	virtual UnexploredRoom  pop(void) = 0;
	virtual int				size(void) = 0;
};
