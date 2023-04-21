#pragma once
#include "Position.h"

class Position;
class PowerPill
{
public:
	PowerPill();

	Position GetPosition();
	void InitPosition();
	void ChangePosition();
	void RevertPosition();

	static PowerPill* GetInstance();
private:
	Position powerpillPosition;
};

