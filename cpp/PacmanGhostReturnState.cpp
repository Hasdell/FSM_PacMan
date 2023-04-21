#include <Windows.h>
#include "PacmanGhostReturnState.h"
#include "PacmanGhostReadyState.h"
#include "PacmanDefineHeader.h"


PacmanGhostReturnState::~PacmanGhostReturnState()
{
	if (GetInstance() != nullptr)
		delete GetInstance();
}
void PacmanGhostReturnState::Execute(PacmanGhost* ghost)
{
	Sleep(GhostSpeed);

	ghost->Return();

	if (ghost->IsDefaultPositionArrive())
		ghost->ChangeState(PacmanGhostReadyState::GetInstance());
}
PacmanGhostReturnState* PacmanGhostReturnState::GetInstance()
{
	static PacmanGhostReturnState* instance;
	if (instance == nullptr)
		instance = new PacmanGhostReturnState;
	return instance;
}