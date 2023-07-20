#include "stdafx.h"
#include "Boss.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "scene.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Bullet.h"


void Boss::Init()
{
	SpriteGo::Init();

	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossIdle.csv"));
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossRightMove.csv"));
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossLeftMove.csv"));
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossAction.csv"));

	bossAnimation.SetTarget(&sprite);

	SetOrigin(Origins::MC);
}

void Boss::Reset()
{
	SpriteGo::Reset();

	SetPosition(gameView.left + gameView.width / 2, gameView.top -100.f);
	bossAnimation.Play("BossIdle");
	SetOrigin(origin);
	SetActive(true);
	action = false;
	speed = 0.0f;
	timer = 0.f;
	dir = { 0.f,0.f };
	count = 0;
	hp=maxHp;
}

void Boss::Release()
{
	SpriteGo::Release();

	SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
	pool->Return(this->hitbox);
}

void Boss::Update(float dt)
{
	SpriteGo::Update(dt);
	bossAnimation.Update(dt);

	if (player->GetPlaying())
	{

		HitBoxPos();
		//std::cout << delayTime << std::endl;
		//std::cout << hp << std::endl;

		if (!action)
		{
			actionNum = Utils::RandomRange(1, 4);
			action = true;
		}
		else if (action && actionNum == 1)
		{
			Patten1();
		}
		else if (action && actionNum == 2)
		{
			Patten2();
		}
		else if (action && actionNum == 3)
		{
			Patten3();

		}

		if (delay)
		{
			delayTime -= dt;
		}

		if (!move)
		{
			dir = { 0.f,0.f };
		}

		timer += dt * speed;

		if (timer > 1.f)
		{
			timer = 1.f;
		}

		Move();


		if (curve && !strike)
		{
			position = BezierMove(startMovePos, middleMovePos, endMovePos, timer);
		}
		else if (!curve && strike)
		{
			position += dir * speed * dt;
		}

		SetPosition(position);
	}
}

void Boss::SetHitBoxPool(ObjectPool<HitboxGo>* hitBoxPool)
{
	this->pool = hitBoxPool;
}

void Boss::SetTargetPos()
{
	targetPos = player->GetPosition();
}

void Boss::SetPlayer(Player* player)
{
	this->player = player;
}

void Boss::Fire()
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
		bullet->BulletStatPos({ position.x,position.y - 25.f });
		bullet->SetCount();
		bullet->SetSpeed(0.f);
		bullet->SetFire(1);
		sceneGame->AddGo(bullet);
	}
}

void Boss::Fire2()
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
		bullet->BulletStatPos({ position.x,position.y - 25.f });
		bullet->SetCount();
		bullet->SetSpeed(0.f);
		bullet->SetFire(2);
		sceneGame->AddGo(bullet);
	}
}

void Boss::Move()
{
	if (bossAnimation.GetCurrIds() != "BossLeftMove")
	{
		if (dir.x < 0)
		{
			bossAnimation.Play("BossLeftMove");
		}
	}
	if (bossAnimation.GetCurrIds() != "BossRightMove")
	{
		if (dir.x > 0)
		{
			bossAnimation.Play("BossRightMove");
		}
	}
	if (bossAnimation.GetCurrIds() != "BossIdle")
	{
		if (dir.x == 0&&!bossPrivatePose)
		{
			bossAnimation.Play("BossIdle");
		}
	}
	if (bossAnimation.GetCurrIds() != "BossAction")
	{
		if (dir.x == 0 && bossPrivatePose)
		{
			bossAnimation.Play("BossAction");
		}
	}
}

sf::Vector2f Boss::BezierMove(const sf::Vector2f& pos0, const sf::Vector2f& pos1, const sf::Vector2f& pos2, float moveT)
{
	float u = 1.f - moveT;
	float tt = moveT * moveT;
	float uu = u * u;

	sf::Vector2f p = uu * pos0;
	p += 2.f * u * moveT * pos1;
	p += tt * pos2;

	return p;
}

void Boss::Patten1()
{
	if(count==0)
	{
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x - 200.f);
		SetEndMovePosY(center.y - 200.f);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
	}
	else if (count == 1)
	{
		move = true;
		SetMiddleMovePosX(center.x);
		SetMiddleMovePosY(center.y);
		SetEndMovePosX(center.x + 300.f);
		SetEndMovePosY(center.y - 250.f);
		SetDirX(1.f);
		SetSpeed(0.5f);
		SetCurve();
		CheckEndPosTypeCurve();
	}
	else if (count == 2)
	{
		move = true;
		SetEndMovePosX(center.x);
		SetEndMovePosY(center.y);
		SetSpeed(400.f);
		Fire();
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
	}
	else if (count == 3)
	{
		move = true;
		SetMiddleMovePosX(center.x-100.f);
		SetMiddleMovePosY(center.y-200.f);
		SetEndMovePosX(center.x - 250.f);
		SetEndMovePosY(center.y - 50.f);
		SetDirX(-1.f);
		SetSpeed(0.5f);
		SetCurve();
		CheckEndPosTypeCurve();
	}
	else if (count == 4)
	{
		SetdelayTime(1.5f);
		TimeOut();
	}
	else if (count == 5)
	{
		PoseFalse();
		action = false;
		count = 0;
	}
}
void Boss::Patten2()
{
	if (count == 0)
	{
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x + 200.f);
		SetEndMovePosY(center.y - 200.f);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
	}
	else if (count == 1)
	{
		move = true;
		SetMiddleMovePosX(center.x);
		SetMiddleMovePosY(center.y);
		SetEndMovePosX(center.x - 300.f);
		SetEndMovePosY(center.y - 250.f);
		SetDirX(-1.f);
		SetSpeed(0.5f);
		SetCurve();
		CheckEndPosTypeCurve();
	}
	else if (count == 2)
	{
		move = true;
		SetEndMovePosX(center.x);
		SetEndMovePosY(center.y);
		SetSpeed(400.f);
		Fire();
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
	}
	else if (count == 3)
	{
		move = true;
		SetMiddleMovePosX(center.x - 100.f);
		SetMiddleMovePosY(center.y - 200.f);
		SetEndMovePosX(center.x + 250.f);
		SetEndMovePosY(center.y - 50.f);
		SetDirX(1.f);
		SetSpeed(0.5f);
		SetCurve();
		CheckEndPosTypeCurve();
	}
	else if (count == 4)
	{
		SetdelayTime(1.5f);
		TimeOut();
	}
	else if (count == 5)
	{
		PoseFalse();
		action = false;
		count = 0;
	}
}
void Boss::Patten3()
{
	if (count == 0)
	{
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x);
		SetEndMovePosY(center.y);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
	}
	else if (count == 1)
	{
		PoseTrue();
		SetdelayTime(1.f);
		Fire2();
		TimeOut();
	}
	else if (count == 2)
	{
		SetdelayTime(5.f);
		TimeOut();
	}
	else if (count == 3)
	{
		PoseFalse();
		action = false;
		count = 0;
	}
}

void Boss::CheckEndPosTypeCurve()
{
	if (position == endMovePos && move)
	{
		move = false;
		speed = 0.f;
		startMovePos = endMovePos;
		pattenActive = false;
		count++;
		timer = 0;
	}
}
void Boss::CheckEndPosTypeStrike()
{
	length = Utils::Distance(position, endMovePos);
	if (length <= 10.f)
	{
		move = false;
		speed = 0.f;
		position = endMovePos;
		startMovePos = endMovePos;
		pattenActive = false;
		count++;
		timer = 0;
	}
}
void Boss::SetStrikeDir()
{
	dir = Utils::Normalize(endMovePos-startMovePos);
}
void Boss::PattenSetPos()
{
	SetStartMovePosX(position.x);
	SetStartMovePosY(position.y);
}
void Boss::SetdelayTime(float t)
{
	if (!delay)
	{
		delay = true;
		delayTime = t;
	}
}
float Boss::GetHitBox()
{
	return this->hitbox->GetRaidus();
}

//gameViewSize.width = 914.5f;
//gameViewSize.height = 640.f;
