#pragma once
#include <string>
#include <iostream>
class Game
{
public:
	Game(std::string gameName);
	Game() {}
	~Game();

	virtual void Start() {}
	virtual void Exit() {}

	std::string GetGameName();
private:
	std::string gameName;

};

