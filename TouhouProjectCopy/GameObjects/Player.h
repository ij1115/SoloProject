#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "ShapeGo.h"

class Bullet;

class Player : public SpriteGo
{
protected:
	AnimationController animation;

	sf::Vector2f dir;

	float speed=600.f;
	float timer = 0.f;
	float attackDelay = 0.05f;

	int boom = 0;

	sf::IntRect playerSkin;

	Bullet* bullet;

public:
	Player(const std::string& textureId= "", const std::string& n= "")
		: SpriteGo(textureId,n) {}
	virtual ~Player() override { Release(); };

	virtual void Init() override;
	virtual void Reset() override;
	
	virtual void Update(float dt) override;

	void MovingLimit();
	void Move();
	void Fire();
};

