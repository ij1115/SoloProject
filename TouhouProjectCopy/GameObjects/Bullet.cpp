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

	sortLayer = 1;

}

void Bullet::Update(float dt)
{
	SpriteGo::Update(dt);

	if (player->GetPlaying())
	{
		
		HitBoxPos();

		if (user == User::Enemy && GrazeCollider() && player->GrazeMode())
		{
			if (player->GetPower() <= 4.0f)
			{
				player->PlusPower(0.05f * dt);
			}
			else if (player->GetPower() > 4.0f)
			{
				player->SetPower(4.0f);
			}
		}

		if (user == User::Player)
		{
			sprite.rotate(720 * dt);
			if (this->type == Types::Type_Two)
			{
				SetDirBossPos();
			}
		}


		if (user == User::Enemy)
		{
			switch (this->setFire)
			{
			case 1:
				BulletPatten1();
				break;
			case 2:
				BulletPatten2();
				break;
			case 3:
				BulletPatten3();
				break;
			case 4:
				BulletPatten4();
				break;
			case 5:
				BulletPatten5();
				break;
			}
		}
		if (delay)
		{
			delayTime -= dt;
		}
		CheckDelay();

		if (user == User::Player && BossCollider() && type == Types::Type_One)
		{
			BulletEffect* effect = effectPool->Get();
			effect->textureId = "graphics/Player.png";
			effect->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Player.png"));
			effect->sprite.setTextureRect(sf::IntRect(177, 160, 16, 17));
			effect->SetPosition(this->GetPosition());
			effect->SetOrigin(Origins::MC);
			effect->SetDirection({0.f, -1.f});
			effect->SetSpeed(50.f);
			effect->SetDuration(0.3f);
			effect->sortLayer = 3;
			SCENE_MGR.GetCurrScene()->AddGo(effect);
			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
			hitboxPool->Return(this->hitbox);
			pool->Return(this);
			player->PlusScore(1);
			boss->BossDamage(9999);
		}
		else if (user == User::Player && BossCollider() && type == Types::Type_Two)
		{
			BulletEffect* effect = effectPool->Get();
			effect->textureId = "graphics/etama6.png";
			effect->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/etama6.png"));
			effect->sprite.setTextureRect(sf::IntRect(35,162, 26, 26));
			effect->SetPosition(this->GetPosition());
			effect->SetOrigin(Origins::MC);
			effect->SetDuration(0.3f);
			effect->sortLayer = 3;
			SCENE_MGR.GetCurrScene()->AddGo(effect);
			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
			hitboxPool->Return(this->hitbox);
			pool->Return(this);
			player->PlusScore(1);
			boss->BossDamage(3);
		}
		else if (user == User::Enemy && PlayerCollider() && !player->GetHitDelay())
		{
			SCENE_MGR.GetCurrScene()->RemoveGo(this);
			SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
			hitboxPool->Return(this->hitbox);
			pool->Return(this);

			for (int i = 0; i < 5; ++i)
			{
				BulletEffect* effect = effectPool->Get();
				effect->textureId = "graphics/Player.png";
				effect->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Player.png"));
				effect->sprite.setTextureRect(sf::IntRect(261, 4, 57, 57));
				effect->SetPosition(player->GetPosition());
				effect->SetOrigin(Origins::MC);
				effect->SetDirection({ Utils::RandomRange(-1.f, 1.f), Utils::RandomRange(-1.f, 1.f) });
				effect->SetDuration(0.3f);
				effect->SetSpeed(300.f);
				effect->sortLayer = 1;
				SCENE_MGR.GetCurrScene()->AddGo(effect);
			}
			player->PlayerDead();
		}


		SetPosition(position + dir * speed * dt);

		Destroy();
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	if (user == User::Enemy)
		window.draw(sprite, sf::BlendAdd);
	else
		window.draw(sprite);
}

void Bullet::SetPool(ObjectPool<Bullet>* bulletPool)
{
	this->pool = bulletPool;
}

void Bullet::SetHitBoxPool(ObjectPool<HitboxGo>* hitboxPool)
{
	this->hitboxPool = hitboxPool;
}

void Bullet::SetEffectPool(ObjectPool<BulletEffect>* effectPool)
{
	this->effectPool = effectPool;
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
	sf::Vector2f temp;
	temp.x= dir.x * std::cos(radian) - dir.y * std::sin(radian);
	temp.y= dir.x * std::sin(radian) + dir.y * std::cos(radian);
	this->dir = temp;
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
		switch (type)
		{

		case Types::Type_One:
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
			break;
		}
		case Types::Type_Two:
		{
			textureId = "graphics/Player.png";
			sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/Player.png"));
			sf::FloatRect tRect;
			tRect.left = 82.f;
			tRect.top = 146.f;
			tRect.width = 14.f;
			tRect.height = 14.f;
			hitbox = hitboxPool->Get();
			hitbox->SetHitBoxSize(7.f);
			hitbox->SetHitBoxFillColor(sf::Color::Transparent);
			hitbox->SetHitBoxOutLineColor(sf::Color::Red);
			hitbox->SetHitBoxOutLineThickness(1);
			hitbox->SetOrigin(Origins::MC);
			hitbox->sortLayer = -2;
			hitbox->SetType(0);
			SCENE_MGR.GetCurrScene()->AddGo(hitbox);
			sprite.setTextureRect((sf::IntRect)tRect);
			break;
		}
		}
	}
	if (user == User::Enemy)
	{
		switch (type)
		{
		case Types::Type_One:
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
			hitbox->SetType(1);
			SCENE_MGR.GetCurrScene()->AddGo(hitbox);
			sprite.setTextureRect((sf::IntRect)tRect);
			break;
		}
		case Types::Type_Two:
		{
			textureId = "graphics/bullet.png";
			sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/bullet.png"));
			sf::FloatRect tRect;
			tRect.left = 1.f;
			tRect.top = 193.f;
			tRect.width = 62.f;
			tRect.height = 62.f;
			hitbox = hitboxPool->Get();
			hitbox->SetHitBoxSize(31.f);
			hitbox->SetHitBoxFillColor(sf::Color::Transparent);
			hitbox->SetHitBoxOutLineColor(sf::Color::Red);
			hitbox->SetHitBoxOutLineThickness(1);
			hitbox->SetOrigin(Origins::MC);
			hitbox->sortLayer = -2;
			hitbox->SetType(1);
			SCENE_MGR.GetCurrScene()->AddGo(hitbox);
			sprite.setTextureRect((sf::IntRect)tRect);
			break;
		}
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

bool Bullet::GrazeCollider()
{
	float disSqur = Utils::Distance(this->hitbox->GetPosition(), player->GetPosition());
	float combinRadius = this->hitbox->GetRaidus() + player->GetGrazeBox();
	if (disSqur <= combinRadius)
	{
		return true;
	}

	return false;
}

bool Bullet::BossCollider()
{
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
		SetDelayTime(0.5f);
	}
	else if (count == 2)
	{
		SetDir({Utils::RandomRange(-1.f,1.f),Utils::RandomRange(-1.f,1.f) });
		CountUp();
	}
	else if (count == 3)
	{
		SetDelayTime(0.5f);
	}
	else if (count == 4)
	{
		SetDirPlayerPos();
		CountUp();
	}
	else if (count == 5)
	{
		SetDelayTime(1.5f);
	}
	else if (count == 6)
	{
		SetDir({0.f,1.f});
		CountUp();
	}
	else if (count == 7)
	{
		SetSpeed(300.f);
		CountUp();
	}
	
}

void Bullet::BulletPatten2()
{
	if (count == 0)
	{
		SetSpeed(0.f);
		CountUp();
	}
	else if (count == 1)
	{
		SetDelayTime(1.f);
	}
	else if (count == 2)
	{
		SetSpeed(700.f);
		CountUp();
	}
}

void Bullet::BulletPatten3()
{
	switch (count)
	{
	case 0:
		SetSpeed(0.f);
		CountUp();
		break;

	case 1:
		SetDelayTime(1.f);
		break;

	case 2:
		SetDirPlayerPos();
		CountUp();
		break;

	case 3:
		SetSpeed(Utils::RandomRange(1000.f, 1300.f));
		CountUp();
		break;
	}


}

void Bullet::BulletPatten4()
{
	switch (count)
	{
	case 0:
		SetSpeed(100.f);
		CountUp();
		break;
	case 1:
		BulletRotate(15);
		CountUp();
		break;
	case 2:
		SetDelayTime(0.1f);
		break;
	case 3:
		BulletRotate(15);
		CountUp();
		break;
	case 4:
		SetDelayTime(0.1f);
		break;
	case 5:
		BulletRotate(15);
		CountUp();
		break;
	case 6:
		SetDelayTime(1.f);
		break;
	case 7:
		BulletRotate(15);
		CountUp();
		break;
	case 8:
		SetDelayTime(0.1f);
		break;
	case 9:
		BulletRotate(15);
		CountUp();
		break;
	case 10:
		SetDelayTime(0.1f);
		break;
	case 11:
		BulletRotate(15);
		CountUp();
		break;
	case 12:
		SetDelayTime(1.f);
		break;
	case 13:
		BulletRotate(15);
		CountUp();
		break;
	case 14:
		SetDelayTime(0.1f);
		break;
	case 15:
		BulletRotate(15);
		CountUp();
		break;
	case 16:
		SetDelayTime(0.1f);
		break;
	case 17:
		BulletRotate(15);
		CountUp();
		break;
	case 18:
		SetDelayTime(1.f);
		break;
	case 19:
		BulletRotate(15);
		CountUp();
		break;
	case 20:
		SetDelayTime(0.1f);
		break;
	case 21:
		BulletRotate(15);
		CountUp();
		break;
	case 22:
		SetDelayTime(0.1f);
		break;
	case 23:
		BulletRotate(15);
		CountUp();
		break;
	case 24:
		SetDelayTime(1.f);
		break;
	case 25:
		BulletRotate(15);
		CountUp();
		break;
	case 26:
		SetDelayTime(0.1f);
		break;
	case 27:
		BulletRotate(15);
		CountUp();
		break;
	case 28:
		SetDelayTime(0.1f);
		break;
	case 29:
		BulletRotate(15);
		CountUp();
		break;
	case 30:
		SetSpeed(600.f);
		CountUp();
		break;
	}
}

void Bullet::BulletPatten5()
{
	switch (count)
	{
	case 0:
		SetSpeed(0.f);
		CountUp();
		break;

	case 1:
		SetDelayTime(1.f);
		break;

	case 2:
		SetSpeed(300.f);
		CountUp();
		break;
	}

}
