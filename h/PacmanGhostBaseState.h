#pragma once
#include "PacmanGhost.h"

class PacmanGhostBaseState
{
public:
	virtual ~PacmanGhostBaseState() {}
	virtual void Execute(PacmanGhost* ghost) = 0;
};

