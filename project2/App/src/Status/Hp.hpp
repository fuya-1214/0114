#pragma once
#include <Siv3D.hpp>

class Hp
{
public:
	struct Style
	{
		ColorF background{ 0.0, 0.6 };
		ColorF delay{ 0.9, 0.8, 0.3 };
		ColorF hpColor{ 0.8, 0.2, 0.2 };
		ColorF frameColor{ 0.1 };
		double frame = 1.5f;
	};

	Hp() noexcept;
	void Update();
	void Draw() const;
	void EnemyDamage(int32 damage);	  // 敵へのダメージ
	void PlayerDamage(int32 damage);  // プレイヤーへのダメージ
	 
	bool enemyAttack = false;

private:
	Effect effect;
	
	double getHPRation() const; // 割合の計算
	double getDelayHPRation() const;
	bool isDead();

	RoundRect m_rect{ 300, 500, 930, 170, 20 };
	const Font fontBit{ 36 };
	const Font fontHp{ 20 };

	int32 maxHP = 400;
	int32 m_maxHP;
	int32 m_currentHP;
	double m_delayHP;
	double m_delayVelocity = 0.0;

	Vec2 enemy = Vec2{ 800, 300 }; // 後から消す
	Vec2 player = Vec2{ 400, 300 };// 後から消す

	double deltaTime;
	const double interval = 1.5;
	double accumulatedTime = 0.0;

	const PixelShader ps;
	double vignetteAlpha = 0.3;
	Image vignetteImage{ Scene::Size(), ColorF{ 178 / 255.0, 34 / 255.0, 34 / 255.0 } };
	const Texture vignetteTexture{ vignetteImage };
	bool isVignette = false;

	double vignetteTime = 0.0;

	const double vignetteFadeIn = 0.1;   // フェードイン時間
	const double vignetteHold = 0.1;   // 最大保持
	const double vignetteFadeOut = 0.3;  // フェードアウト時間

};

struct DamegeEffect : IEffect
{
	Vec2 m_start;
	int32 m_damege;
	Font m_font;

	DamegeEffect(const Vec2& start, int32 damege, const Font& font)
		: m_start(start)
		, m_damege(damege)
		, m_font(font) {}

	bool update(double time) override
	{
		const HSV color{ (180 - m_damege * 1.8), (1.0 - (time * 2.0)) };

		m_font(m_damege).drawAt(TextStyle::Outline(0.2, ColorF{ 0.0, color.a }), 60, m_start.moveBy(0, time * -10), color);

		return (time < 0.5);
	}

};
