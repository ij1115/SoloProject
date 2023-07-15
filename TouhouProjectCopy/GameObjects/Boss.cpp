#include "stdafx.h"
#include "Boss.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "scene.h"
#include "SceneGame.h"
#include "SceneMgr.h"

void Boss::Init()
{
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossIdle.csv"));
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossRightMove.csv"));
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossLeftMove.csv"));

	bossAnimation.SetTarget(&sprite);

	//this->sprite.setScale(1.f, 1.f);

	SetOrigin(Origins::MC);
}

void Boss::Reset()
{
	SetPosition(-250.f, -200.f);
	bossAnimation.Play("BossIdle");
	SetOrigin(origin);
	speed = 600.f;
}

void Boss::Update(float dt)
{
	SpriteGo::Update(dt);
	bossAnimation.Update(dt);

	delayTimer -= dt;

	if (delayTimer < 0.f)
	{
		delayTimer = moveDelayTimer;
		SetTargetPos();
	}
	SetPosition(position + targetPos * speed * dt);
}

void Boss::SetTargetPos()
{
	// x : -795 ~ 15 범위 810 / 5
	// y : -517 ~ 0  범위 517 / 5
}

void Boss::Fire()
{
}
