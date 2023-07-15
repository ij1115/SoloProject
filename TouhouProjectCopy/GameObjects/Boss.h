#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "ShapeGo.h"


class Bullet;

class Boss : public SpriteGo
{
protected:
	AnimationController bossAnimation;

	sf::Vector2f targetPos;

	float speed = 600.f;
	float delayTimer = 0.f;
	float moveDelayTimer = 5.f;

	Bullet* bullet;
public:
	Boss(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Boss() override { Release(); };

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;

	void SetTargetPos();

	void Fire();
};