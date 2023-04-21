#include <Windows.h>
#include "PacmanGhostReadyState.h"
#include "PacmanGhostHunterState.h"
#include "PacmanDefineHeader.h"

PacmanGhostReadyState::~PacmanGhostReadyState()
{
	if (GetInstance() != nullptr)
		delete GetInstance();
}
void PacmanGhostReadyState::Execute(PacmanGhost* ghost)
{
	Sleep(ReadyTime);

	ghost->ChangeState(PacmanGhostHunterState::GetInstance());
}
PacmanGhostReadyState* PacmanGhostReadyState::GetInstance()
{
	static PacmanGhostReadyState* instance;
	if (instance == nullptr)
		instance = new PacmanGhostReadyState;
	return instance;
}