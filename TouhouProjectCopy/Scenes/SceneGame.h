#pragma once
#include "Scene.h"
#include "ObjectPool.h"

class SpriteGo;
class Player;
class Bullet;
class HitboxGo;
class Boss;
class ShapeGo;
class BulletEffect;

class SceneGame : public Scene
{
protected:
	Player* player;
	Boss* boss;
	HitboxGo* pHitbox;
	HitboxGo* bHitbox;
	HitboxGo* grazeBox;
	SpriteGo* graze;
	SpriteGo* immortal;
	SpriteGo* backGround;

	sf::Sound gameMusic;

	sf::FloatRect gameViewSize;

	ObjectPool<Bullet> poolBullet;
	ObjectPool<HitboxGo> poolHitBox;
	ObjectPool<BulletEffect> poolEffect;

	bool playing = false;

	float timer = 0.f;
	int score;

	int num1;
	int num2;
	int num3;
	int num4;
	int num5;

	//Ui
	
		SpriteGo* bossName;
		ShapeGo* bossHp;

		SpriteGo* bossClear;
		SpriteGo* clearFailed;

		SpriteGo* life1;
		SpriteGo* life2;

		std::vector<sf::IntRect> font;

		SpriteGo* timer1;
		SpriteGo* timer2;
		SpriteGo* timer3;
		SpriteGo* timer4;
		SpriteGo* timer5;

		SpriteGo* score1;
		SpriteGo* score2;
		SpriteGo* score3;
		SpriteGo* score4;
		SpriteGo* score5;

		SpriteGo* power1;
		SpriteGo* power2;
		SpriteGo* power3;
		SpriteGo* power4;
		SpriteGo* power5;
	

public:
	SceneGame();
	virtual ~SceneGame() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void GetBullet(Bullet*& bullet);
	template<class T>
	void ClearPool(ObjectPool<T>& pool);

	void TimerFont();
	void PowerFont();
	void ScoreFont();
};

template<class T>
inline void SceneGame::ClearPool(ObjectPool<T>& pool)
{
	for (auto it : pool.GetUseList())
	{
		RemoveGo(it);
	}
	pool.Clear();
}
