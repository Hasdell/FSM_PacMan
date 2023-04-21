#pragma once
#include "Game.h"
#include <vector>

class GameManager
{
public:
	GameManager();
	~GameManager();

	void GameStart();

	static GameManager* GetInstance();
private:
	Game* currentGame;
};