#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "HitboxGo.h"
#include "Player.h"

class Bullet;

class Monster : public SpriteGo
{
protected:
	AnimationController monsterAnimation;

	sf::Vector2f startMovePos;
	sf::Vector2f endMovePos;
	sf::Vector2f middleMovePos;
	sf::Vector2f targetPos;

	float maxHp = 20.f;
	float hp;

	float speed = 600.f;
	float bezierTimer = 0.f;
	float length = 0.f;
	float delayTime = 0.f;

	int actionNum = 0;
	int count;

	int pCount;
	int pMaxCount;
	float pDelay;

	bool pattenActive = false;
	bool move = false;
	bool strike = false;
	bool curve = false;
	bool bossPrivatePose = false;
	bool delay = false;
	bool action = false;

	std::vector<float>* monsterPatten;

	sf::FloatRect gameView;
	sf::Vector2f center;
	sf::Sound hit;
	sf::Sound attack;

	Bullet* bullet;
	Player* player;

	HitboxGo* hitbox;

	ObjectPool<Monster>* poolMonster = nullptr;
	ObjectPool<HitboxGo>* pool = nullptr;
public:
	Monster(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Monster() override { Release(); };

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Release() override;
	virtual void Update(float dt) override;

	void HitBoxSetting();

	void SetPool(ObjectPool<Monster>* monsterPool) { this->poolMonster = monsterPool; }
	void SetHitBoxPool(ObjectPool<HitboxGo>* hitBoxPool) { this->pool = hitBoxPool; }

	void SetGameView(sf::FloatRect size)
	{
		gameView = size;
		center.x = gameView.left + gameView.width / 2;
		center.y = gameView.top + gameView.height / 2;
	}
	void Destroy();

	void SetAction(bool select) { action = select; }
	void SetStartPos(sf::Vector2f pos) { startMovePos = pos; }
	void SetMiddlePos(sf::Vector2f pos) { middleMovePos = pos; }
	void SetEndPos(sf::Vector2f pos) { endMovePos = pos; }

	void SetTargetPos() { targetPos = player->GetPosition(); }
	void SetPlayer(Player* player) { this->player = player; }
	void SetHitBox(HitboxGo* hitbox) { this->hitbox = hitbox; }
	void ActiveHitbox(bool setting) { if (this->hitbox != nullptr)this->hitbox->SetActive(setting); }
	float GetHitBox() { return this->hitbox->GetRaidus(); }
	void MonsterDamage(float damage) {
		hit.play();
		if (hp > 0)hp -= damage;
		if (hp <= 0)
		{
			player->PlusScore(20);
			Destroy();
		}
	}
	float GetBossHp() { return hp; }
	float GetBossMaxHp() { return maxHp; }
	void ResetHP() { hp = maxHp; }
	void SetHP(float hp) { this->hp = hp; }

	void FollowPos() {
		hitbox->SetPosition(position);
	}

	sf::Vector2f BezierMove(const sf::Vector2f& pos0, const sf::Vector2f& pos1, const sf::Vector2f& pos2, float moveT);


	//BulletFire
	void Fire();
	void Fire2();
	void Fire3();
	void Fire4(int c);
	void Fire5(int c);
	void Fire6(int c);
	void Fire7();
	void Fire8();

	//패턴 설정 값
	void SetStartMovePosX(float x) { this->startMovePos.x = x; };
	void SetStartMovePosY(float y) { this->startMovePos.y = y; };
	void SetMiddleMovePosX(float x) { this->middleMovePos.x = x; };
	void SetMiddleMovePosY(float y) { this->middleMovePos.y = y; };
	void SetEndMovePosX(float x) { this->endMovePos.x = x; };
	void SetEndMovePosY(float y) { this->endMovePos.y = y; };
	void SetSpeed(float s) { this->speed = s; }
	void SetCurve() {
		this->curve = true;
		this->strike = false;
	}
	void SetStrike() {
		this->curve = false;
		this->strike = true;
	}
	void PoseTrue() { if (!bossPrivatePose) this->bossPrivatePose = true; }
	void PoseFalse() { if (bossPrivatePose) this->bossPrivatePose = false; }
	void SetdelayTime(float t);
	void TimeOut() {
		if (delayTime < 0.f && delay)
		{
			this->delay = false;
			this->count++;
		}
	}
	void CountUp() { this->count++; }

};

