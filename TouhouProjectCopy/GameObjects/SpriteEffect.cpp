#include "stdafx.h"
#include "SpriteEffect.h"
#include "SceneMgr.h"
#include "Utils.h"

SpriteEffect::SpriteEffect(const std::string& textureId, const std::string& n)
	: SpriteGo(textureId, n)
{

}

void SpriteEffect::Init()
{
	SpriteGo::Init();
	SetOrigin(Origins::MC);
}

void SpriteEffect::Reset()
{
	SpriteGo::Reset();
	timer = 0.f;
	sprite.setColor({ 255, 255, 255, 255 });
}

void SpriteEffect::Update(float dt)
{
	timer += dt;

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
