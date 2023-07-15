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

	this->sprite.setScale(2.2f, 2.2f);

	SetOrigin(Origins::MC);
}

void Player::Reset()
{
	SetPosition(-(FRAMEWORK.GetWindowSize().x / 4), +(FRAMEWORK.GetWindowSize().y/2));
	animation.Play("PlayerIdle");
	SetOrigin(origin);
	speed = 600.f;
	timer = attackDelay;
}

void Player::Update(float dt)
{
	
	dir.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	dir.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);

	MovingLimit();

	timer -= dt;

	if (timer < 0.f && INPUT_MGR.GetKey(sf::Keyboard::Z))
	{
		timer = attackDelay;
		
		std::cout << "attack"<<std::endl;
		Fire();

	}

	SetPosition(position + dir * speed * dt);

	Move();

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::LShift))
	{
		speed = 300.f;
	}
	if (INPUT_MGR.GetKeyUp(sf::Keyboard::LShift))
	{
		speed = 600.f;
	}

	animation.Update(dt);
	SpriteGo::Update(dt);
}

void Player::MovingLimit()
{
	playerSkin = this->sprite.getTextureRect();

	if (position.x < -(FRAMEWORK.GetWindowSize().x / 2)+ 100 + (playerSkin.width / 2))
	{
		position.x = -(FRAMEWORK.GetWindowSize().x / 2) +100+ (playerSkin.width / 2);
	}
	else if (position.x >70 + (playerSkin.width / 2))
	{
		position.x =70 + playerSkin.width / 2;
	}
	if (position.y > (FRAMEWORK.GetWindowSize().y / 2) - 50 - (playerSkin.height / 2))
	{
		position.y = (FRAMEWORK.GetWindowSize().y / 2) - 50 - (playerSkin.height / 2);
	}
	else if (position.y < -(FRAMEWORK.GetWindowSize().y / 2) + 50 + (playerSkin.height / 2))
	{
		position.y = -(FRAMEWORK.GetWindowSize().y / 2) +50+ (playerSkin.height / 2);
	}
}

void Player::Move()
{/*
	std::cout << "pos.x : " << position.x << std::endl;
	std::cout << "pos.y : " << position.y << std::endl << std::endl;*/
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
		bullet->BulletStatPos(position);
		bullet->SetDelCount(0);
		bullet->SetRoCount(0);
		sceneGame->AddGo(bullet);
	}
}

