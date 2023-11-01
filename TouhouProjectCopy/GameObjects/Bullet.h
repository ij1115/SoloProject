#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"
#include "HitboxGo.h"
#include "Monster.h"
#include "Boss.h"
#include "Player.h"
#include "BulletEffect.h"

class Bullet : public SpriteGo
{
public:
	enum class User
	{
		Player,
		Enemy,
	};
	enum class Types
	{
		Type_One,
		Type_Two,
	};
protected:
	bool playing;

	int setFire = 0;
	int count = 0;
	float speed = 1000.f;

	sf::Vector2f dir;
	sf::Vector2f temp;

	bool useRotate = false;
	float rotateRadin = 60.f;

	bool useDelayTime = false;
	float sleepTime = 1.f;
	bool move = true;

	bool delay = false;
	float delayTime = 0.f;
	float deepSleepTimer = 0.f;

	Types type;
	User user;

	sf::Vector2f view;
	sf::FloatRect gameView;

	HitboxGo* hitbox;

	Boss* boss = nullptr;
	Player* player = nullptr;
	Monster* mob = nullptr;

	ObjectPool<Bullet>* pool= nullptr;
	ObjectPool<Monster>* monsterPool = nullptr;
	ObjectPool<HitboxGo>* hitboxPool = nullptr;
	ObjectPool<BulletEffect>* effectPool = nullptr;

public:
	Bullet(const std::string& textureId="", const std::string& n="");
	virtual ~Bullet() override;

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetGameView(sf::FloatRect size) { gameView = size; }
	void GetPlaying(bool playering) { this->playing = &playing; }

	//bullet setting
	void SetPlayer(Player* player) { this->player = player; }
	void SetBoss(Boss* boss) { this->boss = boss; }
	void SetFire(int n) { this->setFire = n; }
	void SetPool(ObjectPool<Bullet>* bulletPool){ this->pool = bulletPool; }
	void SetMonsterPool(ObjectPool<Monster>* monsterPool) { this->monsterPool = monsterPool; }
	void SetHitBoxPool(ObjectPool<HitboxGo>* hitboxPool){ this->hitboxPool = hitboxPool; }
	void SetEffectPool(ObjectPool<BulletEffect>* effectPool){ this->effectPool = effectPool; }
	void SetBulletType(Types pick);
	void SetUser(User pick);
	void SetCount() { this->count =0; }
	void Destroy();
	void SetSpeed(float s) { this->speed = s; }

	bool GrazeCollider();
	bool BossCollider();
	bool MonsterCollider();
	bool PlayerCollider();
	void SetHitBox(HitboxGo* hitbox) { this->hitbox = hitbox; }
	void HitBoxPos() { hitbox->SetPosition(position); }


	//bullet custom
	void SetDir(sf::Vector2f Dir);
	void SetDirBossPos() { dir = Utils::Normalize(boss->GetPosition() - this->position); }
	void SetDirPlayerPos() { dir = Utils::Normalize(player->GetPosition() - this->position); }
	void SetDirMobPos();
	void SetDelayTime(float t) { if (!delay) { this->delay = true; this->delayTime = t; } }
	void CheckDelay();
	void BulletRotate(float count);
	void BulletStartPos(sf::Vector2f Pos){ this->SetPosition(Pos); }
	void CountUp() { this->count++; }

	void FindMob()
	{
		if (monsterPool->GetUseList().empty())
			return;

		mob = monsterPool->GetUseList().front();

		for (auto mobs : monsterPool->GetUseList())
		{
			float disSqur = Utils::Distance(player->GetPosition(), mobs->GetPosition());

			float disSqur_2 = Utils::Distance(player->GetPosition(), mob->GetPosition());
			if (disSqur < disSqur_2)
			{
				mob = mobs;
			}
		}
	}

	//patten
	void BulletPatten1();
	void BulletPatten2(); 
	void BulletPatten3();
	void BulletPatten4();
	void BulletPatten5();
};


