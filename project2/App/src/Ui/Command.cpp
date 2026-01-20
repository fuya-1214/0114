#include "Command.hpp"

Command::Command()
	: attackTexture{ U"assets/attack.png" }
	, attackTexture1{ U"assets/attack1.png" }
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

			attackFlag = true;
		}
	}

	if (special.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);

		if (MouseL.down())
		{
			hp.EnemyDamage(200);

			attackFlag1 = true;
			//hp.enemyAttack = true;
		}
	}

	// 攻撃アニメーションの更新
	if (attackFlag)
	{
		i += Scene::DeltaTime() * 20;
		if (i > 8)
		{
			i = 0;
			attackFlag = false;
		}
	}
	else if (attackFlag1)
	{
		i += Scene::DeltaTime() * 20;
		if (i > 26)
		{
			i = 0;
			attackFlag1 = false;
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

	// 攻撃のアニメーション
	if (attackFlag)
	{
		attackTexture(240 * static_cast<int>(i), 0, 240, 240).drawAt(Vec2{ 1280 / 2 , 250});
	}

	if (attackFlag1)
	{
		attackTexture1(640 * static_cast<int>(i), 0, 640, 480).drawAt(Vec2{ 1280 / 2 , 250});
	}
}
