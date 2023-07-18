#include "stdafx.h"
#include "Bullet.h"
#include "Framework.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "ResourceMgr.h"
#include "ShapeGo.h"

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

	deepSleep = 0.5f;
	sortLayer = 1;
}

void Bullet::Update(float dt)
{
	SpriteGo::Update(dt);
	HitBoxPos();
	delayTime -= dt;
	deepSleep -= dt;

	sprite.rotate(720*dt);

	if (deepSleep < deepSleepTimer && !sleepOn)
	{
		sleepOn = true;
	}

	if (useRotate && rotateCount > 0 && move && sleepOn)
	{
		--rotateCount;
		BulletRotate(rotateRadin);
	}

	if (useDelayTime&& delayCount>0&&move&& sleepOn)
	{	
		move = false;
		temp = dir;
		dir = { 0.f,0.f };
		--delayCount;
		delayTime = sleepTime;
	
	}
	else if (delayTime < 0.f && !move)
	{
		dir = temp;
		move = true;
		BulletRotate(-rotateRadin);
	}

	if (user == User::Player&& BossCollider())
	{
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
		SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
		hitboxPool->Return(this->hitbox);
		pool->Return(this);
		std::cout << "Damage" << std::endl;
	}
	else if(user == User::Enemy&& PlayerCollider())
	{
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
		SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
		hitboxPool->Return(this->hitbox);
		pool->Return(this);
	}

	SetPosition(position + dir * speed * dt);

	Destroy();

}

void Bullet::SetPool(ObjectPool<Bullet>* bulletPool)
{
	this->pool = bulletPool;
}

void Bullet::SetHitBoxPool(ObjectPool<ShapeGo>* hitboxPool)
{
	this->hitboxPool = hitboxPool;
}

void Bullet::BulletRotate(float count)
{
	float radian = count * M_PI / 180;
	dir.x = dir.x * std::cos(radian) - dir.y * std::sin(radian);
	dir.y = dir.x * std::sin(radian) + dir.y * std::cos(radian);
}

void Bullet::BulletStatPos(sf::Vector2f Pos)
{
	SetPosition(Pos);
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
			hitbox->SetHitBoxSize({ 12.f,12.f });
			hitbox->SetHitBoxFillColor(sf::Color::Transparent);
			hitbox->SetHitBoxOutLineColor(sf::Color::Red);
			hitbox->SetHitBoxOutLineThickness(1);
			hitbox->SetOrigin(Origins::MC);
			hitbox->sortLayer = 5;
			hitbox->SetType(0);
			SCENE_MGR.GetCurrScene()->AddGo(hitbox);
			sprite.setTextureRect((sf::IntRect)tRect);
		}
	}
	if (user == User::Enemy)
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
			hitbox->SetHitBoxSize({ 12.f,12.f });
			hitbox->SetHitBoxFillColor(sf::Color::Transparent);
			hitbox->SetHitBoxOutLineColor(sf::Color::Red);
			hitbox->SetHitBoxOutLineThickness(1);
			hitbox->SetOrigin(Origins::MC);
			hitbox->sortLayer = 5;
			hitbox->SetType(0);
			SCENE_MGR.GetCurrScene()->AddGo(hitbox);
			sprite.setTextureRect((sf::IntRect)tRect);
		}
	}
}

void Bullet::SetUser(User pick)
{
	user = pick;
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
	if (position.x > gameView.left + gameView.width + 100.f || position.x < gameView.left -100.f ||
		position.y > gameView.top + gameView.height +100.f || position.y < gameView.top -100.f)
	{
		SCENE_MGR.GetCurrScene()->RemoveGo(this);
		SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
		hitboxPool->Return(this->hitbox);
		pool->Return(this);
	}
}

bool Bullet::BossCollider()
{
	bool a = this->hitbox->GetCollider().intersects(boss->GetHitBox());
	return a;
}

bool Bullet::PlayerCollider()
{
	return this->hitbox->GetCollider().intersects(player->GetHitBox());
}
