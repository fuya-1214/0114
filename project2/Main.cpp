# include <Siv3D.hpp> // Siv3D v0.6.16
#include "App/src/Core/Game.hpp"

void Main()
{
	Window::Resize(1280, 720);
	Game game;

	while (System::Update())
	{
		ClearPrint();

		if (!game.update())break;
		game.draw();

	}
}

