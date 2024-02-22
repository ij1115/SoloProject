#include "stdafx.h"
#include "Monster.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "scene.h"
#include "SceneGame.h"
#include "SceneMgr.h"

#include "Bullet.h"

void Monster::Init()
{
	SpriteGo::Init();

	monsterAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/MonsterIdle.csv"));

	monsterAnimation.SetTarget(&sprite);

	SetOrigin(Origins::MC);
}

void Monster::Reset()
{
	SpriteGo::Reset();

	hit.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/se_damage00.wav"));
	hit.setVolume(25);
	attack.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/se_tan02.wav"));
	attack.setVolume(15);

	monsterAnimation.Play("MonsterIdle");
	SetOrigin(origin);
	SetActive(true);
	speed = 0.0f;
	bezierTimer = 0.f;
	ResetHP();
}

void Monster::Release()
{
	SpriteGo::Release();

	SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
	pool->Return(this->hitbox);
}

void Monster::Update(float dt)
{
	SpriteGo::Update(dt);

	if (player->GetPlaying())
	{
		monsterAnimation.Update(dt);

		if (hitbox != nullptr)
		{
			FollowPos();
		}
		else if (hitbox == nullptr)
		{
			HitBoxSetting();
		}
		
		if (delay)
		{
			delayTime -= dt * speed;
		}

		if (delayTime < 0 && delay)
		{
			delay = false;
			Fire();
			attack.play();
		}

		bezierTimer += dt * speed;

		if (bezierTimer > 1.f)
		{
			bezierTimer = 1.f;

			for (auto mob : poolMonster->GetUseList())
			{
				if(this==mob)
				{
					Destroy();
					return;
				}
			}
		}

		position = BezierMove(startMovePos, middleMovePos, endMovePos, bezierTimer);

		SetPosition(position);
	}
}

sf::Vector2f Monster::BezierMove(const sf::Vector2f& pos0, const sf::Vector2f& pos1, const sf::Vector2f& pos2, float moveT)
{
	float u = 1.f - moveT;
	float tt = moveT * moveT;
	float uu = u * u;

	sf::Vector2f p = uu * pos0;
	p += 2.f * u * moveT * pos1;
	p += tt * pos2;

	return p;
}


void Monster::SetdelayTime(float t)
{
	if (!delay)
	{
		delay = true;
		delayTime = t;
	}
}

void Monster::HitBoxSetting()
{
	SetHitBox(pool->Get());
	hitbox->SetHitBoxSize(20.f);
	hitbox->SetHitBoxFillColor(sf::Color::Transparent);
	hitbox->SetHitBoxOutLineColor(sf::Color::Red);
	hitbox->SetHitBoxOutLineThickness(1);
	hitbox->SetOrigin(Origins::MC);
	hitbox->sortLayer = -2;
	hitbox->SetType(1);
}
void Monster::Destroy()
{
	this->hitbox->Reset();
	this->Reset();
	SCENE_MGR.GetCurrScene()->RemoveGo(this);
	SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
	pool->Return(this->hitbox);
	poolMonster->Return(this);
}
//BulletFire

void Monster::Fire()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (sceneGame != nullptr)
	{
		sceneGame->GetBullet(bullet);
		bullet->SetUser((Bullet::User)1);
		bullet->SetBulletType((Bullet::Types)0);
		bullet->Init();
		bullet->Reset();
		bullet->BulletStartPos({ position.x,position.y - 25.f });
		bullet->SetCount();
		bullet->SetSpeed(300.f);
		bullet->SetDirPlayerPos();
		sceneGame->AddGo(bullet);

	}
}
