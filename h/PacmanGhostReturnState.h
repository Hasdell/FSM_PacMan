#pragma once
#include "PacmanGhostBaseState.h"

class PacmanGhostReturnState : public PacmanGhostBaseState
{
public:
	PacmanGhostReturnState() {}
	~PacmanGhostReturnState();
	void Execute(PacmanGhost* ghost) override;
	static PacmanGhostReturnState* GetInstance();
};

