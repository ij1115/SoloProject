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
	SpriteGo::Init();

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/PlayerIdle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/PlayerRightMove.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/PlayerLeftMove.csv"));

	animation.SetTarget(&sprite);

	SetOrigin(Origins::MC);
}

void Player::Reset()
{
	SpriteGo::Reset();

	Revive();

	animation.Play("PlayerIdle");
	SetOrigin(origin);
	Immortal->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/pl01c.png"));
	playing = true;
	phaseChange = false;
	life = 2;
	score = 0.f;
	power = 0.f;

	pDead.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/se_pldead00.wav"));
	bFire.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/se_graze.wav"));
	bFire.setVolume(20);
}

void Player::Release()
{
	SpriteGo::Release();

	SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
	pool->Return(this->hitbox);
}

void Player::Update(float dt)
{
		SpriteGo::Update(dt);
		if (playing)
		{
			animation.Update(dt);

			FollwoPos();
			SetPosition(position + dir * speed * dt);

			if (hitDelay) // Immortal Time
			{
				hitTimer -= dt;
				Immortal->sprite.rotate(360 * dt);

				if (hitTimer < 0.f)

				{
					hitDelay = false;
					Immortal->SetActive(false);
					pDead.stop();
				}
			}

			if (control && position.y < gameView.top + gameView.height - 50.f)
			{
				control = false;
				speed = 500.f;
			}

			else if (!control)
			{
				dir.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
				dir.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);

				MovingLimit();

				this->timer -= dt;

				if (this->timer < 0.f && INPUT_MGR.GetKey(sf::Keyboard::Z)&&!phaseChange)
				{
					this->timer = attackDelay;

					Fire();
					bFire.play();
				}

				Move();

				if (INPUT_MGR.GetKey(sf::Keyboard::LShift))
				{
					speed = 200.f;
					graze->sortLayer = 0;
					hitbox->sortLayer = 5;
					grazeMode = true;
					graze->sprite.rotate(720 * dt);
				}
				if (INPUT_MGR.GetKeyUp(sf::Keyboard::LShift))
				{
					speed = 500.f;
					graze->sortLayer = -2;
					hitbox->sortLayer = -2;
					grazeMode = false;
				}
			}
		}
}

void Player::Revive()
{
	SetPosition(gameView.left + gameView.width / 2, gameView.top + gameView.height + 50.f);
	dir = { 0.f,-1.f };
	speed = 100.f;
	timer = attackDelay;
	control = true;
	hitDelay = true;
	grazeMode = false;
	graze->sortLayer = -2;
	hitbox->sortLayer = -2;
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

	if (power < 1.0f)
	{
		BulletPower_1();
	}
	else if (power < 2.f)
	{
		BulletPower_1();
		BulletPower_2({ position.x + 20.f,position.y });
		BulletPower_2({ position.x - 20.f,position.y });
	}
	else if (power < 3.f)
	{
		BulletPower_1();
		BulletPower_3();
		BulletPower_4();
		BulletPower_2({ position.x + 20.f,position.y-25.f });
		BulletPower_2({ position.x - 20.f,position.y-25.f });

	}
	else if (power < 4.f)
	{
		BulletPower_1();
		BulletPower_3();
		BulletPower_4();
		BulletPower_2({ position.x + 20.f,position.y - 25.f });
		BulletPower_2({ position.x - 20.f,position.y - 25.f });
		BulletPower_2({ position.x,position.y + 25.f });
	}
	else if (power >= 4.f)
	{
		BulletPower_1();
		BulletPower_3();
		BulletPower_4();
		BulletPower_2({ position.x + 20.f,position.y+25.f });
		BulletPower_2({ position.x + 20.f,position.y-25.f });
		BulletPower_2({ position.x - 20.f,position.y+25.f });
		BulletPower_2({ position.x - 20.f,position.y-25.f });
	}

}
                            
void Player::FollwoPos()
{
	graze->SetPosition(position);
	hitbox->SetPosition(position);
	grazeBox->SetPosition(position);
	Immortal->SetPosition(position);
}

void Player::PlayerDead()
{
	--life;

	if (life>0)
	{
		power -= 1.0f;
		if (power <= 0.f)
		{
			power = 0.f;
		}
		Revive();
		hitTimer = 5.f;
		Immortal->SetActive(true);
	}
	pDead.play();
}

void Player::BulletPower_1()
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
		bullet->BulletStartPos({ position.x,position.y - 25.f });
		bullet->SetSpeed(1000.f);
		sceneGame->AddGo(bullet);
	}
}

void Player::BulletPower_2(sf::Vector2f pos)
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (sceneGame != nullptr)
	{
		sceneGame->GetBullet(bullet);
		bullet->SetUser((Bullet::User)0);
		bullet->SetBulletType((Bullet::Types)1);
		bullet->Init();
		bullet->Reset();
		bullet->BulletStartPos(pos);
		bullet->SetSpeed(1500.f);
		sceneGame->AddGo(bullet);
	}
}

void Player::BulletPower_3()
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
		bullet->BulletStartPos({ position.x-25.f,position.y - 25.f });
		bullet->SetSpeed(1000.f);
		sceneGame->AddGo(bullet);
	}
}

void Player::BulletPower_4()
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
		bullet->BulletStartPos({ position.x+25.f,position.y - 25.f });
		bullet->SetSpeed(1000.f);
		sceneGame->AddGo(bullet);
	}
}

