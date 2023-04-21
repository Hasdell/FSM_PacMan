#include "PacmanGhost.h"
#include "PacmanPlayer.h"
#include "PacmanGameMap.h"
#include "PacmanDefineHeader.h"
#include "PacmanGhostHunterState.h"
#include "PacmanGhostReturnState.h"

PacmanGhost::PacmanGhost()
{
	currentState = PacmanGhostHunterState::GetInstance();
	ghostColor = 0;
	prevPosition.x = 0;
	prevPosition.y = 0;
}

Position PacmanGhost::GetPosition() const
{
	return ghostPosition;
}
void PacmanGhost::SetPosition(int x, int y)
{
	ghostPosition.x = x;
	ghostPosition.y = y;
}

void PacmanGhost::RevertPosition()
{
	ghostPosition = prevPosition;
}

void PacmanGhost::Update()
{
	currentState->Execute(this);
}

void PacmanGhost::Chase()
{
	Move(PathFindingToPlayer());
}
void PacmanGhost::Return()
{
	Move(PathFindingToDefaultPosition());
}
void PacmanGhost::Move(char MoveDir)
{
	Position nextPosition = GetPosition();
	prevPosition = GetPosition();

	switch (MoveDir)
	{
	case PacmanGhost_Move_Up:
		nextPosition.y--;
		break;
	case PacmanGhost_Move_Down:
		nextPosition.y++;
		break;
	case PacmanGhost_Move_Left:
		nextPosition.x--;
		break;
	case PacmanGhost_Move_Right:
		nextPosition.x++;
		break;
	}

	ghostPosition = nextPosition;
}

char PacmanGhost::PathFindingToPlayer()
{
	int yMoveScore[2] = { DefaultScore, DefaultScore }; // 0 - Up, 1 - Down
	int xMoveScore[2] = { DefaultScore, DefaultScore }; // 0 - Left, 1 - Right

	int minScore = 0; // MinCheck
	char bestPath = PacmanGhost_Move_Up;

	int loopCount = 0;

	for (int y = ghostPosition.y - 1; y <= ghostPosition.y + 1; y+=2)
	{
		if (PacmanGameMap::GetInstance()->GetMapCode(ghostPosition.x, y) == PacmanGhostBoxMapCode)
			yMoveScore[loopCount] += 1000;
		else if (PacmanGameMap::GetInstance()->GetMapCode(ghostPosition.x, y) == PacmanGhostMapCode)
			yMoveScore[loopCount] += 900;
		else if (PacmanGameMap::GetInstance()->GetMapCode(ghostPosition.x, y) == PacmanPowerPillMapCode)
			yMoveScore[loopCount] += 100;
		else if (prevPosition.x == ghostPosition.x && prevPosition.y == y)
			yMoveScore[loopCount] += 100;

		yMoveScore[loopCount] += (PacmanPlayer::GetInstance()->GetDistance(ghostPosition.x, y) * DefaultScore);
		
		// +GhostBoxCheck
		if (ghostPosition.x >= GhostBoxMinPositionX && ghostPosition.x <= GhostBoxMaxPositionX)
		{
			if (y >= GhostBoxMinPositionY && y <= GhostBoxMaxPositionY)
			{
				if (!PacmanPlayer::GetInstance()->IsPlayerInGhostBox())
				{
					if (y > (GhostBoxMinPositionY + GhostBoxMaxPositionY) / 2)
					{
						yMoveScore[loopCount] += GhostBoxScore * (GhostBoxMaxPositionY - y + 1);
					}
					else
					{
						yMoveScore[loopCount] += GhostBoxScore * (y - GhostBoxMinPositionY + 1);
					}
				}
			}
		}

		loopCount++;
	}

	loopCount = 0;

	for (int x = ghostPosition.x - 1; x <= ghostPosition.x + 1; x+=2)
	{
		if (PacmanGameMap::GetInstance()->GetMapCode(x, ghostPosition.y) == PacmanGhostBoxMapCode)
			xMoveScore[loopCount] += 1000;
		else if (PacmanGameMap::GetInstance()->GetMapCode(x, ghostPosition.y) == PacmanGhostMapCode)
			xMoveScore[loopCount] += 900;
		else if (PacmanGameMap::GetInstance()->GetMapCode(x, ghostPosition.y) == PacmanPowerPillMapCode)
			xMoveScore[loopCount] += 100;
		else if (prevPosition.x == x && prevPosition.y == ghostPosition.y)
			xMoveScore[loopCount] += 100;

		xMoveScore[loopCount] += (PacmanPlayer::GetInstance()->GetDistance(x, ghostPosition.y) * DefaultScore);
		
		// +GhostBoxCheck
		if (x >= GhostBoxMinPositionX && x <= GhostBoxMaxPositionX)
		{
			if (ghostPosition.y >= GhostBoxMinPositionY && ghostPosition.y <= GhostBoxMaxPositionY)
			{
				if (!PacmanPlayer::GetInstance()->IsPlayerInGhostBox())
				{
					xMoveScore[loopCount] += (abs(x - (GhostBoxMinPositionX + GhostBoxMaxPositionX) / 2) + 1) * GhostBoxScore;
				}
			}
		}

		loopCount++;
	}

	int randomDir = rand() % 4;
	bestPath = randomDir;

	switch (randomDir)
	{
	case PacmanGhost_Move_Up:
		minScore = yMoveScore[0];
		break;
	case PacmanGhost_Move_Down:
		minScore = yMoveScore[1];
		break;
	case PacmanGhost_Move_Left:
		minScore = xMoveScore[0];
		break;
	case PacmanGhost_Move_Right:
		minScore = xMoveScore[1];
		break;
	}

	for (int i = 0; i < sizeof(yMoveScore) / sizeof(int); i++)
	{
		if (minScore > yMoveScore[i])
		{
			minScore = yMoveScore[i];

			if (i == 0)
			{
				bestPath = PacmanGhost_Move_Up;
			}
			else
			{
				bestPath = PacmanGhost_Move_Down;
			}
		}
	}

	for (int i = 0; i < sizeof(xMoveScore) / sizeof(int); i++)
	{
		if (minScore > xMoveScore[i])
		{
			minScore = xMoveScore[i];

			if (i == 0)
			{
				bestPath = PacmanGhost_Move_Left;
			}
			else
			{
				bestPath = PacmanGhost_Move_Right;
			}
		}
	}

	return bestPath;
}
char PacmanGhost::PathFindingToDefaultPosition()
{
	int yMoveScore[2] = { DefaultScore, DefaultScore }; // 0 - Up, 1 - Down
	int xMoveScore[2] = { DefaultScore, DefaultScore }; // 0 - Left, 1 - Right

	int minScore = 0; // MinCheck
	char bestPath = PacmanGhost_Move_Up;

	int loopCount = 0;
	int blockCount = 0;

	for (int y = ghostPosition.y - 1; y <= ghostPosition.y + 1; y += 2)
	{
		if (PacmanGameMap::GetInstance()->GetMapCode(ghostPosition.x, y) == PacmanGhostBoxMapCode)
			yMoveScore[loopCount] += 1000;
		else if (PacmanGameMap::GetInstance()->GetMapCode(ghostPosition.x, y) == PacmanGhostMapCode)
			yMoveScore[loopCount] += 900;
		else if (PacmanGameMap::GetInstance()->GetMapCode(ghostPosition.x, y) == PacmanPowerPillMapCode)
			yMoveScore[loopCount] += 100;
		else if (prevPosition.x == ghostPosition.x && prevPosition.y == y)
			yMoveScore[loopCount] += 100;

		yMoveScore[loopCount] += (GetDistanceToDefaultPosition(ghostPosition.x, y) * DefaultScore);

		for (int x = ghostPosition.x - 1; x <= ghostPosition.x + 1; x++)
		{
			if (PacmanGameMap::GetInstance()->GetMapCode(x, y) == PacmanGhostBoxMapCode)
				blockCount++;
		}

		if (blockCount == 3)
		{
			if (loopCount == 0)
			{
				yMoveScore[loopCount + 1] += 50;
			}
			else
			{
				yMoveScore[loopCount - 1] += 50;
			}
		}

		loopCount++;
	}

	loopCount = 0;
	blockCount = 0;

	for (int x = ghostPosition.x - 1; x <= ghostPosition.x + 1; x += 2)
	{
		if (PacmanGameMap::GetInstance()->GetMapCode(x, ghostPosition.y) == PacmanGhostBoxMapCode)
			xMoveScore[loopCount] += 1000;
		if (PacmanGameMap::GetInstance()->GetMapCode(x, ghostPosition.y) == PacmanGhostMapCode)
			xMoveScore[loopCount] += 900;
		else if (PacmanGameMap::GetInstance()->GetMapCode(x, ghostPosition.y) == PacmanPowerPillMapCode)
			xMoveScore[loopCount] += 100;
		else if (prevPosition.x == x && prevPosition.y == ghostPosition.y)
			xMoveScore[loopCount] += 100;

		xMoveScore[loopCount] += (GetDistanceToDefaultPosition(x, ghostPosition.y) * DefaultScore);

		for (int y = ghostPosition.y - 1; y <= ghostPosition.y + 1; y++)
		{
			if (PacmanGameMap::GetInstance()->GetMapCode(x, y) == PacmanGhostBoxMapCode)
				blockCount++;
		}

		if (blockCount == 3)
		{
			if (loopCount == 0)
			{
				xMoveScore[loopCount + 1] += 50;
			}
			else
			{
				xMoveScore[loopCount - 1] += 50;
			}
		}

		loopCount++;
	}

	int randomDir = rand() % 4;
	bestPath = randomDir;

	switch (randomDir)
	{
	case PacmanGhost_Move_Up:
		minScore = yMoveScore[0];
		break;
	case PacmanGhost_Move_Down:
		minScore = yMoveScore[1];
		break;
	case PacmanGhost_Move_Left:
		minScore = xMoveScore[0];
		break;
	case PacmanGhost_Move_Right:
		minScore = xMoveScore[1];
		break;
	}

	for (int i = 0; i < sizeof(yMoveScore) / sizeof(int); i++)
	{
		if (minScore > yMoveScore[i])
		{
			minScore = yMoveScore[i];

			if (i == 0)
			{
				bestPath = PacmanGhost_Move_Up;
			}
			else
			{
				bestPath = PacmanGhost_Move_Down;
			}
		}
	}

	for (int i = 0; i < sizeof(xMoveScore) / sizeof(int); i++)
	{
		if (minScore > xMoveScore[i])
		{
			minScore = xMoveScore[i];

			if (i == 0)
			{
				bestPath = PacmanGhost_Move_Left;
			}
			else
			{
				bestPath = PacmanGhost_Move_Right;
			}
		}
	}

	return bestPath;
}

bool PacmanGhost::IsDefaultPositionArrive()
{
	switch (ghostColor)
	{
	case GhostColor::RED:
		if (ghostPosition.x == RedGhostDefaultPositionX && ghostPosition.y == RedGhostDefaultPositionY)
			return true;
		break;
	case GhostColor::BLUE:
		if (ghostPosition.x == BlueGhostDefaultPositionX && ghostPosition.y == BlueGhostDefaultPositionY)
			return true;
		break;
	case GhostColor::YELLOW:
		if (ghostPosition.x == YellowGhostDefaultPositionX && ghostPosition.y == YellowGhostDefaultPositionY)
			return true;
		break;
	case GhostColor::PINK:
		if (ghostPosition.x == PinkGhostDefaultPositionX && ghostPosition.y == PinkGhostDefaultPositionY)
			return true;
		break;
	}

	return false;
}

int PacmanGhost::GetDistanceToDefaultPosition(int x, int y)
{
	int distance = 0;

	switch (ghostColor)
	{
	case GhostColor::RED:
		distance = abs(RedGhostDefaultPositionX - x) + abs(RedGhostDefaultPositionY - y);
		break;
	case GhostColor::BLUE:
		distance = abs(BlueGhostDefaultPositionX - x) + abs(BlueGhostDefaultPositionY - y);
		break;
	case GhostColor::YELLOW:
		distance = abs(YellowGhostDefaultPositionX - x) + abs(YellowGhostDefaultPositionY - y);
		break;
	case GhostColor::PINK:
		distance = abs(PinkGhostDefaultPositionX - x) + abs(PinkGhostDefaultPositionY - y);
		break;
	}
	
	return distance;
}

bool PacmanGhost::operator == (const PacmanGhost& anotherGhost)
{
	if (ghostColor == anotherGhost.ghostColor)
		return true;

	return false;
}

void PacmanGhost::ChangeState(PacmanGhostBaseState* state)
{
	currentState = state;
}
PacmanGhostBaseState* PacmanGhost::GetCurrentState()
{
	return currentState;
}