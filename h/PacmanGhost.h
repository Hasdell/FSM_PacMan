#pragma once
#include <vector>
#include "Position.h"

class PacmanGhostBaseState;
class PacmanGhost
{
public:
	PacmanGhost();

	void SetGhostColor(int color) { ghostColor = color; }

	void SetPosition(int x, int y);
	Position GetPosition() const;

	void Update();

	void Chase();
	void Return();
	void Move(char MoveDir);

	char PathFindingToPlayer();
	char PathFindingToDefaultPosition();

	void RevertPosition();

	bool IsDefaultPositionArrive();

	PacmanGhostBaseState* GetCurrentState();

	bool operator == (const PacmanGhost& anotherGhost);

	void ChangeState(PacmanGhostBaseState* state);
private:
	int GetDistanceToDefaultPosition(int x, int y);

	Position ghostPosition;
	Position prevPosition;

	PacmanGhostBaseState* currentState;

	char ghostColor;
};

