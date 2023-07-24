#pragma once
#include "SpriteGo.h"
#include "ObjectPool.h"

class BulletEffect : public SpriteGo
{
protected:
	float duration = 0.f;
	float timer = 0.f;

	sf::Vector2f dir = { 0.f,0.f };
	float speed = 0.f; 

	ObjectPool<BulletEffect>* pool = nullptr;

public:
	BulletEffect(const std::string& textureId = "", const std::string& n = "");
	virtual ~BulletEffect() override { };
	
	void SetSpeed(float speed) { this->speed = speed; }
	void SetDirection(sf::Vector2f direction) { this->dir = direction; }
	void SetDuration(float duration) { this->duration = duration; }
	void SetPool(ObjectPool<BulletEffect>* pool) { this->pool = pool; }

	virtual void Init() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
};

