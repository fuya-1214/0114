#include "Hp.hpp"

Hp::Hp() noexcept
	: m_maxHP{ maxHP }
	, m_currentHP{ maxHP }
	, m_delayHP{ static_cast<double>(maxHP)}
{
}

void Hp::Update()
{
	double smoothTimeSec = 0.4;
	m_delayHP = Math::SmoothDamp(m_delayHP, m_currentHP, m_delayVelocity, smoothTimeSec);

	effect.update();

}

void Hp::Draw() const
{
	const Style& style = Style{};
	const RectF rect = RectF{ 550, 525, 300, 16 };

	// 1. 背景
	rect.draw(style.background);

	// 2. 遅延HP（黄色)
	const double delayWidth = rect.w * getDelayHPRation();
	RectF{ rect.pos, delayWidth, rect.h }.draw(style.delay);

	// 3. 現在のHP（赤）
	const double hpWidth = rect.w * getHPRation();
	RectF{ rect.pos, hpWidth, rect.h }.draw(style.hpColor);

	// 4. 枠線
	rect.drawFrame(style.frame, style.frameColor);

	m_rect.drawFrame(5);
	fontBit(U"プレイヤー").draw(Vec2{ 330, 500 }, ColorF{ 0.2 });
	fontHp(U"HP").draw(Vec2{ 550, 500 }, ColorF{ 0.2 });
	fontHp(ThousandsSeparate(m_currentHP)).draw(Vec2{ 830, 500 }, ColorF{ 0.2 });
}

double Hp::getHPRation() const
{
	return m_maxHP > 0 ? (static_cast<double>(m_currentHP) / m_maxHP) : 0.0;
}

double Hp::getDelayHPRation() const
{
	return m_maxHP > 0 ? (m_delayHP / m_maxHP) : 0.0;
}

void Hp::Damage(int32 damage)
{
	m_currentHP = Max(0, m_currentHP - damage);

	effect.add<DamegeEffect>(Cursor::Pos(), damage, fontBit);
}

bool Hp::isDead()
{
	return m_currentHP <= 0;
}
