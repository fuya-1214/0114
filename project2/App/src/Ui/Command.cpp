#include "Command.hpp"

Command::Command()
{
}

void Command::Update()
{
	if (attack.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);

		if (MouseL.down())
		{
			hp.EnemyDamage(90);
			hp.enemyAttack = true;
		}
	}

	if (special.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);

		if (MouseL.down())
		{
			hp.EnemyDamage(200);
			//hp.enemyAttack = true;
		}
	}

	hp.Update();
}

void Command::Draw() const
{
	commandFlame.drawFrame(5);
	attack.draw();
	special.draw();

	font(U" 攻撃　").draw(Vec2{ 110, 525 }, ColorF{ 0.2 });
	font(U"必殺技").draw(Vec2{ 105, 600 }, ColorF{ 0.2 });

	if (attack.mouseOver())
	{
		attack.draw(ColorF{ 0.8, 0.8, 1.0});
		font(U" 攻撃　").draw(Vec2{ 110, 525 }, ColorF{ 0.2, Periodic::Square0_1(10ms) });
	}

	if (special.mouseOver())
	{
		special.draw(ColorF{ 0.8, 0.8, 1.0});
		font(U"必殺技").draw(Vec2{ 105, 600 }, ColorF{ 0.2, Periodic::Square0_1(10ms) });
	}

	hp.Draw();
}
