#include "stdafx.h"
#include "Bullet.h"
#include "Framework.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "ResourceMgr.h"

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
}

void Bullet::Update(float dt)
{
	SpriteGo::Update(dt);

	delayTime -= dt;
	
	sprite.rotate(720*dt);

	if (useRotate && rotateCount > 0 && move)
	{
		--rotateCount;
		BulletRotate(rotateRadin);
	}

	if (useDelayTime&& delayCount>0&&move)
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
	}



	SetPosition(position + dir * speed * dt);

	Destroy();

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
			sprite.setTextureRect((sf::IntRect)tRect);
		}
	}

}

void Bullet::SetUser(User pick)
{
	this->user = pick;
}

void Bullet::Destroy()
{
	std::cout << "pos.x :" << position.x << std::endl << std::endl;
	std::cout << "pos.y :" << position.y << std::endl << std::endl;
	if ((position.x > 100 || position.x < -(view.x / 2)) ||
		(position.y > (view.y / 2)|| position.y < -(view.y / 2)))
	{
		SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrScene());
		if (scene != nullptr)
		{
			scene->PoolActive(this);
		}
	}
}
