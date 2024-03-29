#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "ObjectPool.h"
#include "HitboxGo.h"

class Bullet;

class Player : public SpriteGo
{
protected:
	AnimationController animation;
	sf::Sound pDead;
	sf::Sound bFire;

	sf::Vector2f dir;

	bool playing;
	bool phaseChange;
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

	Bullet* bullet = nullptr;
	HitboxGo* hitbox= nullptr;
	SpriteGo* Immortal = nullptr;
	SpriteGo* graze = nullptr;
	HitboxGo* grazeBox = nullptr;

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

	void SetHitBoxPool(ObjectPool<HitboxGo>* hitBoxPool) { this->pool = hitBoxPool; }

	void SetGameView(sf::FloatRect size) { gameView = size; }

	void MovingLimit();
	void Move();
	void Fire();
	void FollwoPos();
	void PlayerDead();

	void SetImmortal(SpriteGo* sprite) { this->Immortal = sprite; }
	void SetGraze(SpriteGo* sprite) { this->graze = sprite; }
	void SetHitBox(HitboxGo* shape) { this->hitbox = shape; }
	void SetGrazeBox(HitboxGo* shape) { this->grazeBox = shape; }
	void ActiveHitbox(bool setting) { if(this->hitbox!=nullptr)this->hitbox->SetActive(setting); }
	void ActiveGrazebox(bool setting) { if (this->grazeBox != nullptr)this->grazeBox->SetActive(setting); }
	void ActiveGraze(bool setting) { if (this->graze != nullptr)this->graze->SetActive(setting); }
	
	float GetHitBox() { return this->hitbox->GetRaidus(); }
	float GetGrazeBox(){ return this->grazeBox->GetRaidus(); }
	bool GetHitDelay() { return hitDelay; }
	void SetHitDelay(float t) { hitTimer = t; }

	void SetPlaying(bool play) { playing = play; }
	bool GetPlaying() { return playing; }
	void SetChangePhase(bool phase) { phaseChange = phase; }
	bool GetChangePhase() { return phaseChange; }
	bool GrazeMode() { return grazeMode; }

	int GetLife() { return life; }
	void LifeDown() { --life; }
	void SetLife(int l) { life = l; }

	int GetScore() { return score; }
	void SetScore(int i) { score = i; }
	void PlusScore(int i) { score += i; }

	float GetPower() { return power; }
	void SetPower(float i) { power = i; }
	void PlusPower(float i) { power += i; }

	void BulletPower_1();
	void BulletPower_2(sf::Vector2f pos);
	void BulletPower_3();
	void BulletPower_4();

	void Revive();
};

