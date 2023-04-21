#pragma once
#include "Position.h"

class PacmanPlayer
{
public:
	PacmanPlayer() {}
	~PacmanPlayer()
	{
		if (GetInstance() != nullptr)
			delete GetInstance();
	}

	void SetPosition(int x, int y);
	Position GetPosition() const;

	void MoveCheck();

	bool IsPlayerInGhostBox();

	int GetDistance(int x, int y);

	static PacmanPlayer* GetInstance();
private:
	bool MapCodeCheck(int x, int y);

	Position playerPosition;
};

