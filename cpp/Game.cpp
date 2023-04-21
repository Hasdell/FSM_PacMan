#include "Game.h"

Game::Game(std::string gameName)
{
	this->gameName = gameName;
}
Game::~Game()
{

}

std::string Game::GetGameName()
{
	return gameName;
}