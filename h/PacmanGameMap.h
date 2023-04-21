#pragma once
#include <vector>

class PacmanPlayer;
class PacmanGhost;
class Position;
class PacmanGameMap
{
public:
	PacmanGameMap();
	~PacmanGameMap();

	void InitMap(std::vector<PacmanGhost>& ghostList);
	void InitGhostBox();

	void DrawMap(int eatCount);

	void UpdateMap(std::vector<PacmanGhost>& ghostList, int eatCount);

	static PacmanGameMap* GetInstance();

	int GetMapCode(int x, int y);
private:
	char** map;
	std::vector<Position> ghostBoxPositionList;

	Position prevPlayerPosition;
	std::vector<Position> prevGhostPosition;
};

