#pragma once
class Position
{
public:
	bool operator == (const Position& anotherPosition)
	{
		if (x == anotherPosition.x && y == anotherPosition.y)
			return true;

		return false;
	}

	int x, y;
};

