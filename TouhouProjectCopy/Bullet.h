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
	float rotateRadin = 10.f;
	int rotateCount = 2;

	bool useDelayTime = false;
	float delayTime = 0.f;
	float sleepTime = 2.f;
	int delayCount = 1;
	bool move = true;

	Types type;
	User user;

	sf::Vector2f view;

	ObjectPool<Bullet>* pool;
public:
	Bullet(const std::string& textureId="", const std::string& n="");
	virtual ~Bullet() override;

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;

	void BulletRotate(float count);
	void BulletStatPos(sf::Vector2f Pos);
	void SetDir(sf::Vector2f Dir);
	void SetBulletType(Types pick);
	void SetUser(User pick);

	void Destroy();
//Ãæµ¹  {}
};

