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
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossIdle.csv"));
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossRightMove.csv"));
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossLeftMove.csv"));
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossAction.csv"));

	bossAnimation.SetTarget(&sprite);
	
	
	//this->sprite.setScale(1.f, 1.f);

	SetOrigin(Origins::MC);
}

void Boss::Reset()
{
	SetPosition(gameView.left + gameView.width / 2, gameView.top + 100.f);
	bossAnimation.Play("BossIdle");
	SetOrigin(origin);
	speed = 0.0f;
	timer = 0.f;
	dir = { 0.f,0.f };
	count = 0;
}

void Boss::Update(float dt)
{
	SpriteGo::Update(dt);
	bossAnimation.Update(dt);
	HitBoxPos();
	std::cout << delayTime << std::endl;
	Patten1();
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


	if(curve&&!strike)
	{ 
		position = BezierMove(startMovePos, middleMovePos, endMovePos, timer);
	}
	else if(!curve&&strike)
	{
		position += dir * speed * dt;
	}

	SetPosition(position);
}

void Boss::SetPoolSetPool(ObjectPool<ShapeGo>* hitBoxPool)
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
		SetSpeed(300.f);
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
		PoseTrue();
		SetdelayTime(15.f);
		TimeOut();
	}
	if (count == 5)
	{
		PoseFalse();
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
	if (length <= 0.5f)
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

//gameViewSize.width = 914.5f;
//gameViewSize.height = 640.f;
