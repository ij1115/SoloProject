#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "ShapeGo.h"

class Bullet;
class Player;

class Boss : public SpriteGo
{
protected:
	AnimationController bossAnimation;

	sf::Vector2f startMovePos;
	sf::Vector2f endMovePos;
	sf::Vector2f middleMovePos;
	sf::Vector2f targetPos;
	sf::Vector2f dir;

	float maxHp=2000.f;
	float hp;

	float speed = 600.f;
	float timer = 0.f;
	float length = 0.f;
	float delayTime = 0.f;

	int pCount;
	int pMaxCount;

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

	Bullet* bullet;
	Player* player;
	ShapeGo* hitbox;

	ObjectPool<ShapeGo>* pool = nullptr;
public:
	Boss(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Boss() override { Release(); };

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Release() override;
	virtual void Update(float dt) override;


	void SetHitBoxPool(ObjectPool<ShapeGo>* hitBoxPool);

	void SetGameView(sf::FloatRect size)
	{
		gameView = size;
		center.x = gameView.left + gameView.width / 2;
		center.y = gameView.top + gameView.height / 2;
	}

	void SetTargetPos();
	void SetPlayer(Player* player);
	void SetHitBox(ShapeGo* hitbox) { this->hitbox = hitbox; }
	void HitBoxPos() { hitbox->SetPosition(position); }
	void Fire();
	void Fire2();
	void Move();
	sf::Vector2f BezierMove(const sf::Vector2f& pos0, const sf::Vector2f& pos1, const sf::Vector2f& pos2, float moveT);

	void Patten1();
	void Patten2();
	void Patten3();

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

	void BossDamage(float damage) { hp -= damage; }
	float GetBossHp() { return hp; }

};