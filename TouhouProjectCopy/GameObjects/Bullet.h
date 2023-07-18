#pragma once
#include "SpriteGo.h"
#include "Boss.h"
#include "Player.h"
#include "ObjectPool.h"

class ShapeGo;

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
		Shape,
		Line,
	};
protected:
	int setFire = 0;
	int count = 0;
	float speed = 1000.f;

	sf::Vector2f dir;
	sf::Vector2f temp;

	bool useRotate = false;
	float rotateRadin = 60.f;
	int rotateCount = 0;

	bool useDelayTime = false;
	float sleepTime = 1.f;
	int delayCount = 0;
	bool move = true;

	bool delay = false;
	float delayTime = 0.f;
	float deepSleepTimer = 0.f;

	Types type;
	User user;

	sf::Vector2f view;
	sf::FloatRect gameView;

	ShapeGo* hitbox;

	Boss* boss = nullptr;
	Player* player = nullptr;

	ObjectPool<Bullet>* pool= nullptr;
	ObjectPool<ShapeGo>* hitboxPool = nullptr;

public:
	Bullet(const std::string& textureId="", const std::string& n="");
	virtual ~Bullet() override;

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetGameView(sf::FloatRect size) { gameView = size; }

	//bullet setting
	void SetFire(int n) { this->setFire = n; }
	void SetPlayer(Player* player) { this->player = player; }
	void SetBoss(Boss* boss) { this->boss = boss; }
	void SetPool(ObjectPool<Bullet>* bulletPool);
	void SetHitBoxPool(ObjectPool<ShapeGo>* hitboxPool);
	void SetBulletType(Types pick);
	void SetUser(User pick);
	void SetCount() { this->count =0; }
	void Destroy();
	void SetSpeed(float s) { this->speed = s; }

	bool BossCollider();
	bool PlayerCollider();
	void SetHitBox(ShapeGo* hitbox) { this->hitbox = hitbox; }
	void HitBoxPos() { hitbox->SetPosition(position); }


	//bullet custom
	void SetDir(sf::Vector2f Dir);
	void SetDirPlayerPos() { dir = Utils::Normalize(player->GetPosition() - this->position); }
	void SetDelayTime(float t) { if (!delay) { this->delay = true; this->delayTime = t; } }
	void CheckDelay();
	void BulletRotate(float count);
	void BulletStatPos(sf::Vector2f Pos);


	void SetRoCount(int i);
	void SetDelCount(int i);

	void CountUp() { this->count++; }
	//patten
	void BulletPatten1();
	void BulletPatten2();
//Ãæµ¹  {}
};

