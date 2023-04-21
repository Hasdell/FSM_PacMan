#pragma once
#include "PacmanGhostBaseState.h"

class PacmanGhostHunterState : public PacmanGhostBaseState
{
public:
	PacmanGhostHunterState() {}
	~PacmanGhostHunterState();
	void Execute(PacmanGhost* ghost) override;
	static PacmanGhostHunterState* GetInstance();
};

