#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "ObjectPool.h"

class HitboxGo;
class Bullet;

class Player : public SpriteGo
{
protected:
	AnimationController animation;
	sf::Sound pDead;
	sf::Sound bFire;

	sf::Vector2f dir;

	bool playing;
	bool control = true;
	bool hitDelay = true;
	bool grazeMode = false;

	float hitTimer = 0.f;

	float speed=600.f;
	float timer = 0.f;
	float attackDelay = 0.05f;

	int life = 0;
	int score = 0;
	float power = 0.f;
	int boom = 0;

	Bullet* bullet = nullptr;
	HitboxGo* hitbox=nullptr;
	SpriteGo* Immortal = nullptr;
	SpriteGo* graze = nullptr;
	HitboxGo* grazeBox =nullptr;

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

	void SetImmortal(SpriteGo* sprite) { this->Immortal = sprite; }
	void SetGraze(SpriteGo* sprite) { this->graze = sprite; }
	void SetHitBox(HitboxGo* shape) { this->hitbox = shape; }
	void SetGrazeBox(HitboxGo* shape) { this->grazeBox = shape; }
	void FollwoPos();

	float GetHitBox();
	float GetGrazeBox();
	bool GetHitDelay() { return hitDelay; }
	void SetHitDelay(float t) { hitTimer = t; }
	void PlayerDead();
	void LifeDown() { --life; }
	int GetLife() { return life; }
	void SetLife(int l) { life = l; }
	void SetPlaying(bool play) { playing = play; }
	bool GetPlaying() { return playing; }
	bool GrazeMode() { return grazeMode; }
	void SetScore(int i) { score = i; }
	void PlusScore(int i) { score += i; }
	int GetScore() { return score; }
	float GetPower() { return power; }
	void SetPower(float i) { power = i; }
	void PlusPower(float i) { power += i; }

	void BulletPower_1();
	void BulletPower_2(sf::Vector2f pos);
	void BulletPower_3();
	void BulletPower_4();
};

