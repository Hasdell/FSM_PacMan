#include <random>
#include "PowerPill.h"
#include "PacmanDefineHeader.h"

PowerPill::PowerPill()
{
	powerpillPosition.x = 1;
	powerpillPosition.y = 1;
}
Position PowerPill::GetPosition()
{
	return powerpillPosition;
}
void PowerPill::InitPosition()
{
	ChangePosition();
}
void PowerPill::ChangePosition()
{
	int x = (rand() % (GameMapSizeX - 2)) + 1;
	int y = (rand() % (GameMapSizeY - 2)) + 1;

	powerpillPosition.x = x;
	powerpillPosition.y = y;
}

PowerPill* PowerPill::GetInstance()
{
	static PowerPill* instance;
	if (instance == nullptr)
		instance = new PowerPill;
	return instance;
}