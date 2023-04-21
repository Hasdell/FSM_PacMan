#include <iostream>
#include <thread>

#include "PacmanPlayer.h"
#include "PowerPill.h"

#include "PacmanGhost.h"
#include "PacmanGhostReturnState.h"

#include "PacmanGameMap.h"
#include "PacmanDefineHeader.h"
#include "DoubleBuffering.h"

PacmanGameMap::PacmanGameMap()
{
	map = new char*[GameMapSizeY + 1];
	for (int i = 0; i < GameMapSizeY; i++)
		map[i] = new char[GameMapSizeX];
}

PacmanGameMap::~PacmanGameMap()
{
	for (int i = 0; i < GameMapSizeY; i++)
		delete[] map[i];
	delete[] map;

	if (GetInstance() != nullptr)
		delete GetInstance();
}

void PacmanGameMap::InitGhostBox()
{
	Position ghostBoxPosition;

	for (int y = 0; y < GameMapSizeY; y++)
	{
		for (int x = 0; x < GameMapSizeX; x++)
		{
			if (x >= GhostBoxMinPositionX && x <= GhostBoxMaxPositionX && y >= GhostBoxMinPositionY && y <= GhostBoxMaxPositionY)
			{
				if (x == (GhostBoxMinPositionX + GhostBoxMaxPositionX) / 2 || x == ((GhostBoxMinPositionX + GhostBoxMaxPositionX) / 2) + 1)
					continue;
				if (x > GhostBoxMinPositionX && x < GhostBoxMaxPositionX)
				{
					if (y > GhostBoxMinPositionY && y < GhostBoxMaxPositionY)
						continue;
				}
				ghostBoxPosition.x = x;
				ghostBoxPosition.y = y;
				ghostBoxPositionList.push_back(ghostBoxPosition);
			}
		}
	}
}
void PacmanGameMap::InitMap(std::vector<PacmanGhost>& ghostList)
{
	InitGhostBox();

	for (int y = 0; y < GameMapSizeY; y++)
	{
		for (int x = 0; x < GameMapSizeX; x++)
		{
			map[y][x] = PacmanEmptyMapCode;

			if (x == 0 || x == GameMapSizeX - 1)
				map[y][x] = PacmanWallMapCode;
			if (y == 0 || y == GameMapSizeY - 1)
				map[y][x] = PacmanWallMapCode;
		}
	}

	map[PacmanPlayer::GetInstance()->GetPosition().y][PacmanPlayer::GetInstance()->GetPosition().x] = PacmanPlayerMapCode;

	prevPlayerPosition = PacmanPlayer::GetInstance()->GetPosition();

	map[PowerPill::GetInstance()->GetPosition().y][PowerPill::GetInstance()->GetPosition().x] = PacmanPowerPillMapCode;

	for (int i = 0; i < ghostList.size(); i++)
	{
		map[ghostList[i].GetPosition().y][ghostList[i].GetPosition().x] = PacmanGhostMapCode;

		prevGhostPosition.push_back(ghostList[i].GetPosition());
	}

	for (int i = 0; i < ghostBoxPositionList.size(); i++)
	{
		map[ghostBoxPositionList[i].y][ghostBoxPositionList[i].x] = PacmanGhostBoxMapCode;
	}

	DrawMap(0);
}

void PacmanGameMap::DrawMap(int eatCount)
{
	char eatCountString[10];

	_itoa_s(eatCount, eatCountString, 10);

	ScreenClear();
	for (int y = 0; y < GameMapSizeY; y++)
	{
		for (int x = 0; x < GameMapSizeX; x++)
		{
			if (map[y][x] == PacmanPlayerMapCode)
				ScreenPrint(x, y, "P");
			else if (map[y][x] == PacmanGhostMapCode)
				ScreenPrint(x, y, "G");
			else if (map[y][x] == PacmanGhostReturnMapCode)
				ScreenPrint(x, y, "X");
			else if (map[y][x] == PacmanGhostBoxMapCode)
				ScreenPrint(x, y, "B");
			else if (map[y][x] == PacmanWallMapCode)
				ScreenPrint(x, y, "W");
			else if (map[y][x] == PacmanPowerPillMapCode)
				ScreenPrint(x, y, "E");
		}
		std::cout << std::endl;
	}
	ScreenPrint(GameMapSizeX + 5, GameMapSizeY / 2, "EatCount == 10 is win");
	ScreenPrint(GameMapSizeX + 5, (GameMapSizeY / 2) + 1, "EatCount : ");
	ScreenPrint(GameMapSizeX + 16, (GameMapSizeY / 2) + 1, eatCountString);
	ScreenFlipping();
}

void PacmanGameMap::UpdateMap(std::vector<PacmanGhost>& ghostList, int eatCount)
{
	map[prevPlayerPosition.y][prevPlayerPosition.x] = PacmanEmptyMapCode;

	for (int i = 0; i < prevGhostPosition.size(); i++)
		map[prevGhostPosition[i].y][prevGhostPosition[i].x] = PacmanEmptyMapCode;
	prevGhostPosition.clear();

	map[PacmanPlayer::GetInstance()->GetPosition().y][PacmanPlayer::GetInstance()->GetPosition().x] = PacmanPlayerMapCode;
	prevPlayerPosition = PacmanPlayer::GetInstance()->GetPosition();

	map[PowerPill::GetInstance()->GetPosition().y][PowerPill::GetInstance()->GetPosition().x] = PacmanPowerPillMapCode;

	for (int i = 0; i < ghostList.size(); i++)
	{
		if (ghostList[i].GetCurrentState() == PacmanGhostReturnState::GetInstance())
			map[ghostList[i].GetPosition().y][ghostList[i].GetPosition().x] = PacmanGhostReturnMapCode;
		else
			map[ghostList[i].GetPosition().y][ghostList[i].GetPosition().x] = PacmanGhostMapCode;
		prevGhostPosition.push_back(ghostList[i].GetPosition());
	}
	
	DrawMap(eatCount);
}
int PacmanGameMap::GetMapCode(int x, int y)
{
	return map[y][x];
}

PacmanGameMap* PacmanGameMap::GetInstance()
{
	static PacmanGameMap* instance;
	if (instance == nullptr)
		instance = new PacmanGameMap;
	return instance;
}