#pragma once
#include "SpriteGo.h"
#include "Player.h"
#include "ObjectPool.h"

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

	ObjectPool<Bullet>* pool= nullptr;

public:
	Bullet(const std::string& textureId="", const std::string& n="");
	virtual ~Bullet() override;

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetPool(ObjectPool<Bullet>* bulletPool);
	void BulletRotate(float count);
	void BulletStatPos(sf::Vector2f Pos);
	void SetDir(sf::Vector2f Dir);
	void SetBulletType(Types pick);
	void SetUser(User pick);

	void SetRoCount(int i);
	void SetDelCount(int i);

	void Destroy();

	void SetGameView(sf::FloatRect size) { gameView = size; }
//Ãæµ¹  {}
};

