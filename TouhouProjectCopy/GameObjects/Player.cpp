#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "scene.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "Bullet.h"

void Player::Init()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/PlayerIdle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/PlayerRightMove.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/PlayerLeftMove.csv"));

	animation.SetTarget(&sprite);

	SetOrigin(Origins::MC);
}

void Player::Reset()
{
	SetPosition(gameView.left+gameView.width/2, gameView.top + gameView.height + 50.f);
	dir = { 0.f,-1.f };
	animation.Play("PlayerIdle");
	SetOrigin(origin);
	speed = 100.f;
	timer = attackDelay;
}

void Player::Release()
{
	SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
	pool->Return(this->hitbox);
}

void Player::Update(float dt)
{
	HitBoxPos();
	SetPosition(position + dir * speed * dt);

	if (control && position.y  < gameView.top + gameView.height -50.f)
	{
		control = false;
		speed = 500.f;
	}
	else if (!control)
	{
		dir.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
		dir.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);

		MovingLimit();

		timer -= dt;

		if (timer < 0.f && INPUT_MGR.GetKey(sf::Keyboard::Z))
		{
			timer = attackDelay;

			//std::cout << "attack" << std::endl;
			Fire();
		}

		Move();

		if (INPUT_MGR.GetKeyDown(sf::Keyboard::LShift))
		{
			speed = 200.f;
		}

		if (INPUT_MGR.GetKeyUp(sf::Keyboard::LShift))
		{
			speed = 500.f;

		}
	}

	animation.Update(dt);
	SpriteGo::Update(dt);
}

void Player::SetHitBoxPool(ObjectPool<ShapeGo>* hitBoxPool)
{
	this->pool = hitBoxPool;
}

void Player::MovingLimit()
{
	if (position.x < gameView.left+15.f)
	{
		position.x = gameView.left +15.f;
	}
	else if (position.x > gameView.left + gameView.width  - 15.f)
	{
		position.x = gameView.left + gameView.width - 15.f;
	}
	if (position.y > gameView.top + gameView.height - 25.f)
	{
		position.y = gameView.top + gameView.height -25.f;
	}
	else if (position.y < gameView.top+25)
	{
		position.y = gameView.top+25;
	}
}

void Player::Move()
{
	if (animation.GetCurrIds() != "PlayerLeftMove")
	{
		if (dir.x < 0)
		{
			animation.Play("PlayerLeftMove");
		}
	}
	if (animation.GetCurrIds() != "PlayerRightMove")
	{
		if (dir.x > 0)
		{
			animation.Play("PlayerRightMove");
		}
	}
	if (animation.GetCurrIds() != "PlayerIdle")
	{
		if (dir.x == 0)
		{
			animation.Play("PlayerIdle");
		}
	}
}

void Player::Fire()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (sceneGame != nullptr)
	{
		sceneGame->GetBullet(bullet);
		bullet->SetUser((Bullet::User)0);
		bullet->SetBulletType((Bullet::Types)0);
		bullet->Init();
		bullet->Reset();
		bullet->SetDir({ 0.f, -1.f });
		bullet->BulletStatPos({ position.x,position.y-25.f});
		bullet->SetDelCount(0);
		bullet->SetRoCount(0);
		sceneGame->AddGo(bullet);
	}
}

void Player::HitBoxPos()
{
	hitbox->SetPosition(position);
}

sf::FloatRect Player::GetHitBox()
{
	return this->hitbox->GetCollider();
}
