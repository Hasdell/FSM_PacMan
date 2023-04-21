#include <conio.h>
#include <thread>
#include "PacmanPlayer.h"
#include "PacmanDefineHeader.h"
#include "PacmanGameMap.h"

enum PacmanPlayerMoveDir
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77
};
void PacmanPlayer::SetPosition(int x, int y)
{
	playerPosition.x = x;
	playerPosition.y = y;
}

Position PacmanPlayer::GetPosition() const
{
	return playerPosition;
}
int PacmanPlayer::GetDistance(int x, int y)
{
	return abs(playerPosition.x - x) + abs(playerPosition.y - y);
}

void PacmanPlayer::MoveCheck()
{
	if (_kbhit())
	{
		int key = _getch();

		switch (key)
		{
		case PacmanPlayerMoveDir::UP:
			if (MapCodeCheck(playerPosition.x, playerPosition.y - 1))
			{
				playerPosition.y--;
			}
			break;
		case PacmanPlayerMoveDir::RIGHT:
			if (MapCodeCheck(playerPosition.x + 1, playerPosition.y))
			{
				playerPosition.x++;
			}
			break;
		case PacmanPlayerMoveDir::DOWN:
			if (MapCodeCheck(playerPosition.x, playerPosition.y + 1))
			{
				playerPosition.y++;
			}
			break;
		case PacmanPlayerMoveDir::LEFT:
			if (MapCodeCheck(playerPosition.x - 1, playerPosition.y))
			{
				playerPosition.x--;
			}
			break;
		}
	}
}
bool PacmanPlayer::MapCodeCheck(int x, int y)
{
	if (PacmanGameMap::GetInstance()->GetMapCode(x, y) == PacmanEmptyMapCode || 
		PacmanGameMap::GetInstance()->GetMapCode(x, y) == PacmanPowerPillMapCode ||
		PacmanGameMap::GetInstance()->GetMapCode(x, y) == PacmanGhostMapCode)
		return true;
	return false;
}

bool PacmanPlayer::IsPlayerInGhostBox()
{
	if (playerPosition.x >= GhostBoxMinPositionX && playerPosition.x <= GhostBoxMaxPositionX)
	{
		if (playerPosition.y >= GhostBoxMinPositionY && playerPosition.y <= GhostBoxMaxPositionY)
		{
			return true;
		}
	}

	return false;
}

PacmanPlayer* PacmanPlayer::GetInstance()
{
	static PacmanPlayer* instance;
	if(instance == nullptr)
		instance = new PacmanPlayer();
	return instance;
}
