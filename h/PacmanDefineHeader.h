#pragma once

#define GameMapSizeX 60
#define GameMapSizeY 18

#define PacmanPlayerMapCode 0
#define PacmanGhostMapCode 1
#define PacmanGhostReturnMapCode 2

#define PacmanEmptyMapCode 4
#define PacmanWallMapCode 5
#define PacmanGhostBoxMapCode 6

#define PacmanPowerPillMapCode 7

#define GhostBoxMinPositionX 40
#define GhostBoxMinPositionY 5

#define GhostBoxMaxPositionX 50
#define GhostBoxMaxPositionY 10

#define GhostCount 4

#define GhostSpeed 300 // ms
#define ReadyTime 2000

#define DefaultScore 10
#define GhostBoxScore 20

#define PacmanGhost_Move_Up 0
#define PacmanGhost_Move_Down 1
#define PacmanGhost_Move_Left 2
#define PacmanGhost_Move_Right 3

#define PacmanDefaultPositionX 3
#define PacmanDefaultPositionY 5

#define RedGhostDefaultPositionX 43
#define RedGhostDefaultPositionY 7

#define BlueGhostDefaultPositionX 43
#define BlueGhostDefaultPositionY 8

#define YellowGhostDefaultPositionX 48
#define YellowGhostDefaultPositionY 7

#define PinkGhostDefaultPositionX 48
#define PinkGhostDefaultPositionY 8

enum GhostColor
{
	RED,
	BLUE,
	YELLOW,
	PINK
};