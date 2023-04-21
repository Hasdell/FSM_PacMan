#include "GameManager.h"
#include "PacmanGame.h"
#include <iostream>

GameManager::GameManager()
{
	currentGame = new PacmanGame("Pacman");
}
GameManager::~GameManager()
{
	if (GetInstance() != nullptr)
		delete GetInstance();
	if (currentGame != nullptr)
		delete currentGame;
}

void GameManager::GameStart()
{
	currentGame->Start();
}

GameManager* GameManager::GetInstance()
{
	static GameManager* instance;
	if (instance == nullptr)
		instance = new GameManager;
	return instance;
}