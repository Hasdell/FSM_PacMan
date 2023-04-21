#include <Windows.h>
#include "PacmanGhostHunterState.h"
#include "PacmanDefineHeader.h"

PacmanGhostHunterState::~PacmanGhostHunterState()
{
	if (GetInstance() != nullptr)
		delete GetInstance();
}
void PacmanGhostHunterState::Execute(PacmanGhost* ghost)
{
	Sleep(GhostSpeed);

	ghost->Chase();
}
PacmanGhostHunterState* PacmanGhostHunterState::GetInstance()
{
	static PacmanGhostHunterState* instance;
	if (instance == nullptr)
		instance = new PacmanGhostHunterState();
	return instance;
}