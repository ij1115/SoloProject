#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "HitboxGo.h"

class Bullet;

class Player : public SpriteGo
{
protected:
	AnimationController animation;

	sf::Vector2f dir;

	bool playing;
	bool control = true;
	bool hitDelay = true;

	float hitTimer = 0.f;

	float speed=600.f;
	float timer = 0.f;
	float attackDelay = 0.05f;

	int life = 0;
	int score = 0;
	int boom = 0;

	Bullet* bullet;
	HitboxGo* hitbox;
	HitboxGo* powerUp;

	sf::FloatRect gameView;
	ObjectPool<HitboxGo>* pool = nullptr;
public:
	Player(const std::string& textureId= "", const std::string& n= "")
		: SpriteGo(textureId,n) {}
	virtual ~Player() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Release() override;
	virtual void Update(float dt) override;

	void SetHitBoxPool(ObjectPool<HitboxGo>* hitBoxPool);

	void SetGameView(sf::FloatRect size) { gameView = size; }

	void MovingLimit();
	void Move();
	void Fire();

	void SetHitBox(HitboxGo* shape) { this->hitbox = shape; }
	void HitBoxPos();

	float GetHitBox();
	bool GetHitDelay() { return hitDelay; }
	void SetHitDelay(float t) { hitTimer = t; }
	void LifeDown() { --life; }
	int GetLife() { return life; }
	void SetLife(int l) { life = l; }
	void SetPlaying(bool play) { playing = play; }
	bool GetPlaying() { return playing; }
	void SetScore(int i) { score = i; }
	void PlusScore(int i) { score += i; }
	int GetScore() { return score; }
};

