#pragma once
#include "PacmanGhostBaseState.h"

class PacmanGhostReadyState : public PacmanGhostBaseState
{
public:
	PacmanGhostReadyState() {}
	~PacmanGhostReadyState();
	void Execute(PacmanGhost* ghost);
	static PacmanGhostReadyState* GetInstance();
};

