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
	float speed = 1000.f;

	sf::Vector2f dir;
	sf::Vector2f temp;

	bool useRotate = false;
	float rotateRadin = 60.f;
	int rotateCount = 0;

	bool useDelayTime = false;
	float delayTime = 0.f;
	float sleepTime = 1.f;
	int delayCount = 0;
	bool move = true;

	bool sleepOn = false;
	float deepSleep = 5.f;
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

	void SetPlayer(Player* player) { this->player = player; }
	void SetBoss(Boss* boss) { this->boss = boss; }
	void SetPool(ObjectPool<Bullet>* bulletPool);
	void SetHitBoxPool(ObjectPool<ShapeGo>* hitboxPool);

	void BulletRotate(float count);
	void BulletStatPos(sf::Vector2f Pos);
	void SetDir(sf::Vector2f Dir);
	void SetBulletType(Types pick);
	void SetUser(User pick);

	void SetHitBox(ShapeGo* hitbox) { this->hitbox = hitbox; }
	void HitBoxPos(){ hitbox->SetPosition(position); }
	void SetRoCount(int i);
	void SetDelCount(int i);

	void Destroy();

	bool BossCollider();
	bool PlayerCollider();

	void SetGameView(sf::FloatRect size) { gameView = size; }
//Ãæµ¹  {}
};

