#include <iostream>
#include "GameManager.h"
#include "DoubleBuffering.h"

void main()
{
	ScreenInit();
	srand((unsigned)time(NULL));
	GameManager::GetInstance()->GameStart();
}