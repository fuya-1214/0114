#pragma once
#include <Siv3D.hpp>
#include "../Status/Hp.hpp"

class Command
{
public:
	Command();
	void Update();
	void Draw() const;

private:
	Hp hp;

	const Font fontBitmap{ 48 };
	RoundRect commandFlame{ 50, 500, 200, 170, 20 };
	Rect attack{ 75, 525, 150, 50 };
	Rect special{ 75, 600, 150, 50 };

	const Font font{ 28 };

	bool attackFlag = false;
	const Texture attackTexture;

	bool attackFlag1 = false;
	const Texture attackTexture1;
	double i = 0;

};
