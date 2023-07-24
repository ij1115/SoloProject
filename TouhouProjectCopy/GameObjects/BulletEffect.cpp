#include "stdafx.h"
#include "BulletEffect.h"
#include "SceneMgr.h"
#include "Utils.h"

BulletEffect::BulletEffect(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{
}

void BulletEffect::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void BulletEffect::Reset()
{
	SpriteGo::Reset();
	timer = 0.f;
	sprite.setColor({ 255, 255, 255, 255 });
}

void BulletEffect::Update(float dt)
{
	SpriteGo::Update(dt);

	timer += dt;

	SetPosition(position + dir * speed * dt);
	sprite.rotate(720*dt);

	sprite.setColor({ 255, 255, 255, (sf::Uint8)Utils::Lerp(255-(255*(timer/duration)), 0, timer)});

	if (timer > duration)
	{
		if (pool != nullptr)
		{
			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			pool->Return(this);
		}
		else
		{
			SetActive(false);
		}
	}
}
