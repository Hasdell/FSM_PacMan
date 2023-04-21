#pragma once
#include <vector>
#include "PacmanGhost.h"

class Game;
class PacmanGhost;
class PacmanGame : public Game
{
public:
	PacmanGame(std::string gameName);
	~PacmanGame() {}

	void Start() override;
	void Exit() override;

	void CheckGameOver();

	void GameMapUpdate();
	void PlayerUpdate();
	void PowerPillUpdate();
	void GhostUpdate(int GhostColor);
private:
	std::vector<PacmanGhost> ghostList;

	bool bIsGameOver;
	bool bIsPlayerEatPowerPill;

	int eatCount;
};

