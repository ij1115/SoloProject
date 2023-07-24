#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "HitboxGo.h"

class Player;
class Bullet;

class Boss : public SpriteGo
{
protected:
	AnimationController bossAnimation;

	sf::Vector2f startMovePos;
	sf::Vector2f endMovePos;
	sf::Vector2f middleMovePos;
	sf::Vector2f targetPos;
	sf::Vector2f dir;

	float maxHp=10000.f;
	float hp;

	float speed = 600.f;
	float timer = 0.f;
	float length = 0.f;
	float delayTime = 0.f;

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
	int actionNum = 0;
	//시험용
	int count;
	//코드
	std::vector<float>* bossPatten;

	sf::FloatRect gameView;
	sf::Vector2f center;
	sf::Sound hit;

	Bullet* bullet;
	Player* player;
	HitboxGo* hitbox;

	ObjectPool<HitboxGo>* pool = nullptr;
public:
	Boss(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Boss() override { Release(); };

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Release() override;
	virtual void Update(float dt) override;


	void SetHitBoxPool(ObjectPool<HitboxGo>* hitBoxPool);

	void SetGameView(sf::FloatRect size)
	{
		gameView = size;
		center.x = gameView.left + gameView.width / 2;
		center.y = gameView.top + gameView.height / 2;
	}

	void SetTargetPos();
	void SetPlayer(Player* player);
	void SetHitBox(HitboxGo* hitbox) { this->hitbox = hitbox; }
	void HitBoxPos() { hitbox->SetPosition(position); }
	void Fire();
	void Fire2();
	void Fire3();
	void Fire4(int c);
	void Move();
	sf::Vector2f BezierMove(const sf::Vector2f& pos0, const sf::Vector2f& pos1, const sf::Vector2f& pos2, float moveT);

	void Patten1();
	void Patten2();
	void Patten3();
	void Patten4();
	void Patten5();

	//패턴 설정 값
	void SetStartMovePosX(float x) { this->startMovePos.x = x; };
	void SetStartMovePosY(float y) { this->startMovePos.y = y; };
	void SetMiddleMovePosX(float x) { this->middleMovePos.x = x; };
	void SetMiddleMovePosY(float y) { this->middleMovePos.y = y; };
	void SetEndMovePosX(float x) { this->endMovePos.x = x; };
	void SetEndMovePosY(float y) { this->endMovePos.y = y; };
	void SetDirX(float x) { this->dir.x = x; };
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
	void CheckEndPosTypeCurve();
	void CheckEndPosTypeStrike();
	void SetStrikeDir();
	void PattenSetPos();
	void SetdelayTime(float t);
	void TimeOut() {
		if (delayTime < 0.f && delay)
		{
			this->delay = false;
			this->count++;
		}
	}
	void CountUp() { this->count++; }
	

	float GetHitBox();

	void BossDamage(float damage) {
		hit.play();
		if (hp > 0)hp -= damage;
		else if (hp < 0)hp = 0.f;
	}
	float GetBossHp() { return hp; }
	float GetBossMaxHp() { return maxHp; }
};