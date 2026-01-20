#include "Game.hpp"

Game::Game()
{
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
}

bool Game::update()
{
	command.Update();
	return true;
}

void Game::draw() const
{
	command.Draw();
}
