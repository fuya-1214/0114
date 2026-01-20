#pragma once
#include <Siv3D.hpp>
#include "../Ui/Command.hpp"

class Game
{
public:
	Game();
	bool update();
	void draw() const;

private:
	Command command;
};
