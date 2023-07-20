#include "stdafx.h"
#include "Bullet.h"
#include "Framework.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "ResourceMgr.h"
#include "HitboxGo.h"

Bullet::Bullet(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId,n)
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	SpriteGo::Init();

	view = FRAMEWORK.GetWindowSize();

	SetOrigin(Origins::MC);
}

void Bullet::Reset()
{
	SpriteGo::Reset();

	float speed = 0.f;
	useDelayTime = true;
	useRotate = true;
	sprite.setRotation(0.0f);
	dir = { 0.f,0.f };

	sortLayer = 1;
}

void Bullet::Update(float dt)
{
	SpriteGo::Update(dt);

	if (player->GetPlaying())
	{

		HitBoxPos();

		if (user == User::Player)
			sprite.rotate(720 * dt);

		if (user == User::Enemy)
		{
			if (setFire == 1)
			{
				BulletPatten1();
			}
			if (setFire == 2)
			{
				BulletPatten2();
			}
		}
		if (delay)
		{
			delayTime -= dt;
		}
		CheckDelay();
		SetPosition(position + dir * speed * dt);

		//if (useRotate && rotateCount > 0 && move)
		//{
		//	--rotateCount;
		//	BulletRotate(rotateRadin);
		//}

		//if (useDelayTime&& delayCount>0&&move)
		//{	
		//	move = false;
		//	temp = dir;
		//	dir = { 0.f,0.f };
		//	--delayCount;
		//	delayTime = sleepTime;
		//
		//}
		//else if (delayTime < 0.f && !move)
		//{
		//	dir = temp;
		//	move = true;
		//	BulletRotate(-rotateRadin);
		//}

		if (user == User::Player && BossCollider())
		{
			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
			hitboxPool->Return(this->hitbox);
			pool->Return(this);
			player->PlusScore(1);
			boss->BossDamage(5);
		}
		else if (user == User::Enemy && PlayerCollider() && !player->GetHitDelay())
		{
			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
			hitboxPool->Return(this->hitbox);
			pool->Return(this);

			player->LifeDown();
			if (player->GetLife())
			{
				player->Reset();
			}
			player->SetHitDelay(5.f);
		}

		Destroy();
	}
}

void Bullet::SetPool(ObjectPool<Bullet>* bulletPool)
{
	this->pool = bulletPool;
}

void Bullet::SetHitBoxPool(ObjectPool<HitboxGo>* hitboxPool)
{
	this->hitboxPool = hitboxPool;
}

void Bullet::CheckDelay()
{
	if (delay && delayTime < 0.f)
	{
		this->delay = false;
		this->count++;
	}
}

void Bullet::BulletRotate(float count)
{
	float radian = count * M_PI / 180;
	this->dir.x = dir.x * std::cos(radian) - dir.y * std::sin(radian);
	this->dir.y = dir.x * std::sin(radian) + dir.y * std::cos(radian);
}

void Bullet::BulletStatPos(sf::Vector2f Pos)
{
	this->SetPosition(Pos);
}

void Bullet::SetDir(sf::Vector2f Dir)
{
	this->dir = Utils::Normalize(Dir);
}

void Bullet::SetBulletType(Types pick)
{
	this->type = pick;

	if(user==User::Player)
	{
		if (type == Types::Shape)
		{
			textureId = "graphics/Player.png";
			sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Player.png"));
			sf::FloatRect tRect;
			tRect.left = 1.f;
			tRect.top = 147.f;
			tRect.width = 16.f;
			tRect.height = 12.f;
			hitbox = hitboxPool->Get();
			hitbox->SetHitBoxSize(6.f);
			hitbox->SetHitBoxFillColor(sf::Color::Transparent);
			hitbox->SetHitBoxOutLineColor(sf::Color::Red);
			hitbox->SetHitBoxOutLineThickness(1);
			hitbox->SetOrigin(Origins::MC);
			hitbox->sortLayer = -2;
			hitbox->SetType(0);
			SCENE_MGR.GetCurrScene()->AddGo(hitbox);
			sprite.setTextureRect((sf::IntRect)tRect);
		}
	}
	if (user == User::Enemy)
	{
		if (type == Types::Shape)
		{
			textureId = "graphics/bullet.png";
			sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/bullet.png"));
			sf::FloatRect tRect;
			tRect.left = 194.f;
			tRect.top = 33.f;
			tRect.width = 30.f;
			tRect.height = 30.f;
			hitbox = hitboxPool->Get();
			hitbox->SetHitBoxSize(13.f);
			hitbox->SetHitBoxFillColor(sf::Color::Transparent);
			hitbox->SetHitBoxOutLineColor(sf::Color::Red);
			hitbox->SetHitBoxOutLineThickness(1);
			hitbox->SetOrigin(Origins::MC);
			hitbox->sortLayer = -2;
			hitbox->SetType(0);
			SCENE_MGR.GetCurrScene()->AddGo(hitbox);
			sprite.setTextureRect((sf::IntRect)tRect);
		}
	}
}

void Bullet::SetUser(User pick)
{
	this->user = pick;
}

void Bullet::SetRoCount(int i)
{
	rotateCount = i;
}

void Bullet::SetDelCount(int i)
{
	delayCount = i;
}

void Bullet::Destroy()
{
	if (this->position.x > gameView.left + gameView.width + 100.f || this->position.x < gameView.left -100.f ||
		this->position.y > gameView.top + gameView.height +100.f || this->position.y < gameView.top -100.f)
	{
		this->hitbox->Reset();
		this->Reset();
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
		SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
		hitboxPool->Return(this->hitbox);
		pool->Return(this);
	}
}

bool Bullet::BossCollider()
{
	// 화살 포지션 - 몬스터 포지션 < 화살 반지름 + 몬스터 반지름

	float disSqur = Utils::Distance(this->hitbox->GetPosition(), boss->GetPosition());
	float combinRadius = this->hitbox->GetRaidus() + boss->GetHitBox();
	if (disSqur <= combinRadius)
	{
		return true;
	}

	return false;
}

bool Bullet::PlayerCollider()
{
	float disSqur = Utils::Distance(this->hitbox->GetPosition(), player->GetPosition());
	float combinRadius = this->hitbox->GetRaidus() + player->GetHitBox();
	if (disSqur <= combinRadius)
	{
		return true;
	}

	return false;
}

void Bullet::BulletPatten1()
{
	if(count==0)
	{
		SetSpeed(300.f);
		SetDirPlayerPos();
		CountUp();
	}
	else if(count==1)
	{
		SetDelayTime(1.f);
	}
	else if (count == 2)
	{
		SetDir({Utils::RandomRange(-1.f,1.f),Utils::RandomRange(-1.f,1.f) });
		CountUp();
	}
	else if (count == 3)
	{
		SetDelayTime(1.f);
	}
	else if (count == 4)
	{
		SetDirPlayerPos();
		CountUp();
	}
	else if (count == 5)
	{
		SetDelayTime(2.f);
	}
	else if (count == 6)
	{
		SetDir({0.f,1.f});
		CountUp();
	}
	else if (count == 7)
	{
		SetSpeed(500.f);
		CountUp();
	}
	
}

void Bullet::BulletPatten2()
{
	if (count == 0)
	{
		SetSpeed(0.f);
		SetDir({ Utils::RandomRange(-1.f,1.f),Utils::RandomRange(-1.f,1.f) });
		CountUp();
	}
	else if (count == 1)
	{
		SetDelayTime(5.f);
	}
	else if (count == 2)
	{
		SetSpeed(150.f);
		CountUp();
	}
}
