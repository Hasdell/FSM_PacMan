#include <iostream>
#include <thread>

#include "PowerPill.h"
#include "PacmanPlayer.h"

#include "PacmanGhost.h"
#include "PacmanGhostHunterState.h"
#include "PacmanGhostReturnState.h"

#include "Game.h"
#include "PacmanGame.h"
#include "PacmanGameMap.h"
#include "PacmanDefineHeader.h"
#include "DoubleBuffering.h"

PacmanGame::PacmanGame(std::string gameName) : Game(gameName)
{
	bIsGameOver = false;
	bIsPlayerEatPowerPill = false;

	eatCount = 0;

	for (int i = 0; i < GhostCount; i++)
	{
		PacmanGhost newGhost;

		switch (i)
		{
		case GhostColor::RED:
			newGhost.SetPosition(RedGhostDefaultPositionX, RedGhostDefaultPositionY);
			newGhost.SetGhostColor(GhostColor::RED);
			break;
		case GhostColor::BLUE:
			newGhost.SetPosition(BlueGhostDefaultPositionX, BlueGhostDefaultPositionY);
			newGhost.SetGhostColor(GhostColor::BLUE);
			break;
		case GhostColor::YELLOW:
			newGhost.SetPosition(YellowGhostDefaultPositionX, YellowGhostDefaultPositionY);
			newGhost.SetGhostColor(GhostColor::YELLOW);
			break;
		case GhostColor::PINK:
			newGhost.SetPosition(PinkGhostDefaultPositionX, PinkGhostDefaultPositionY);
			newGhost.SetGhostColor(GhostColor::PINK);
			break;
		default:
			Exit();
			return;
		}

		ghostList.push_back(newGhost);
	}
	
	PacmanPlayer::GetInstance()->SetPosition(PacmanDefaultPositionX, PacmanDefaultPositionY);

	PowerPill::GetInstance()->InitPosition();

	PacmanGameMap::GetInstance()->InitMap(ghostList);
}
void PacmanGame::Start()
{
	std::thread playerUpdateThread = std::thread(&PacmanGame::PlayerUpdate, this);

	std::thread gameMapUpdateThread = std::thread(&PacmanGame::GameMapUpdate, this);

	std::thread powerpillUpdateThread = std::thread(&PacmanGame::PowerPillUpdate, this);

	std::thread redGhostUpdateThread = std::thread(&PacmanGame::GhostUpdate, this, 0);
	std::thread blueGhostUpdateThread = std::thread(&PacmanGame::GhostUpdate, this, 1);
	std::thread yellowGhostUpdateThread = std::thread(&PacmanGame::GhostUpdate, this, 2);
	std::thread pinkGhostUpdateThread = std::thread(&PacmanGame::GhostUpdate, this, 3);

	std::thread gameoverCheckThread = std::thread(&PacmanGame::CheckGameOver, this);

	playerUpdateThread.join();

	powerpillUpdateThread.join();

	redGhostUpdateThread.join();
	blueGhostUpdateThread.join();
	yellowGhostUpdateThread.join();
	pinkGhostUpdateThread.join();

	gameMapUpdateThread.join();

	gameoverCheckThread.join();
}
void PacmanGame::Exit()
{
	std::cout << "팩맨 게임이 종료되었습니다." << std::endl;
	
	if (eatCount == 10)
	{
		std::cout << "게임 결과 : 승리";
	}
	else
	{
		std::cout << "게임 결과 : 패배";
	}
}
void PacmanGame::GameMapUpdate()
{
	while (1)
	{
		if (bIsGameOver)
			return;

		PacmanGameMap::GetInstance()->UpdateMap(ghostList, eatCount);
	}
}
void PacmanGame::PlayerUpdate()
{
	while (1)
	{
		if (bIsGameOver)
			return;

		PacmanPlayer::GetInstance()->MoveCheck();

		
		if (PacmanPlayer::GetInstance()->GetPosition() == PowerPill::GetInstance()->GetPosition())
		{
			bIsPlayerEatPowerPill = true;

			eatCount++;
			
			for (int i = 0; i < GhostCount; i++)
			{
				ghostList[i].ChangeState(PacmanGhostReturnState::GetInstance());
			}
		}
	}
}
void PacmanGame::PowerPillUpdate()
{
	while (1)
	{
		if (bIsGameOver)
			return;

		if (!bIsPlayerEatPowerPill)
			continue;

		PowerPill::GetInstance()->ChangePosition();

		if (PowerPill::GetInstance()->GetPosition() == PacmanPlayer::GetInstance()->GetPosition())
			continue;
		
		for (int i = 0; i < GhostCount; i++)
		{
			if (PowerPill::GetInstance()->GetPosition() == ghostList[i].GetPosition())
				continue;
		}

		if (PowerPill::GetInstance()->GetPosition().x >= GhostBoxMinPositionX && PowerPill::GetInstance()->GetPosition().x <= GhostBoxMaxPositionX)
		{
			if (PowerPill::GetInstance()->GetPosition().y >= GhostBoxMinPositionY && PowerPill::GetInstance()->GetPosition().y <= GhostBoxMaxPositionY)
			{
				continue;
			}
		}
		
		bIsPlayerEatPowerPill = false;
		
	}
}
void PacmanGame::GhostUpdate(int GhostColor)
{
	while (1)
	{
		if (bIsGameOver)
			return;

		ghostList[GhostColor].Update();

		for (int i = 0; i < GhostCount - 1; i++)
		{
			if (ghostList[i] == ghostList[GhostColor])
				continue;

			if (ghostList[i].GetPosition() == ghostList[GhostColor].GetPosition())
				ghostList[GhostColor].RevertPosition();
		}
	}
}

void PacmanGame::CheckGameOver()
{
	while (1)
	{
		if (bIsGameOver)
			return;

		if (eatCount == 10)
		{
			bIsGameOver = true;
			Exit();
			return;
		}

		for (int i = 0; i < GhostCount; i++)
		{
			if (PacmanPlayer::GetInstance()->GetPosition().x == ghostList[i].GetPosition().x && PacmanPlayer::GetInstance()->GetPosition().y == ghostList[i].GetPosition().y)
			{
				if (ghostList[i].GetCurrentState() != PacmanGhostHunterState::GetInstance())
					continue;

				bIsGameOver = true;
				Exit();
				return;
			}
		}
	}
}