#pragma once
#include "Scene.h"
#include "ObjectPool.h"
#include "AnimationController.h"
class SpriteGo;
class Player;
class Bullet;
class HitboxGo;
class Boss;
class ShapeGo;
class BulletEffect;
class Monster;

class SceneGame : public Scene
{
protected:
	UpdateState currentUpdate;

	AnimationController endingAni;

	Player* player;
	Boss* boss;

	SpriteGo* backGround;
	SpriteGo* ending;

	sf::Vector2f backGroundScale = { 3.f,3.f };

	sf::Sound gameMusic;
	sf::Sound se_Sound;
	sf::Sound se_pickSound;
	sf::Sound se_pause;

	sf::FloatRect gameViewSize;

	ObjectPool<Bullet> poolBullet;
	ObjectPool<HitboxGo> poolHitBox;
	ObjectPool<BulletEffect> poolEffect;
	ObjectPool<Monster> poolMonster;

	bool playing = false;
	bool phaseChange = false;
	bool scaleChange = false;
	bool pause = false;
	bool realyYN = false;
	bool clear = false;
	bool endingScene = false;

	bool flip = true;

	bool spawn = true;

	float spawnTimer;


	float timer = 0.f;
	float changeClearTime = 1.0f;
	float changeTimer = 0.f;
	int score;

	//Ui
		ShapeGo* bossHp;
		SpriteGo* bossName;
		SpriteGo* bossClear;
		SpriteGo* clearFailed;

		std::vector<SpriteGo*> life;

		std::vector<sf::IntRect> font;
		std::vector<SpriteGo*> numberUiFont;
		//0~4 timer font
		//5~9 score font
		//10~14 power font

		int pauseMenuSelect = 0;
		int realySelect = 0;

		ShapeGo* pauseBackGround;
		std::vector<SpriteGo*> pauseUi;
		// 0 pauseBar;
		// 1 pauseMenu;
		// 2 returnToGame;
		// 3 returnToTitle;
		// 4 giveUpToReplay;
		// 5 realyBar;
		// 6 realy;
		// 7 yes;
		// 8 no;
	
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

	void PlayUpdate(float dt);
	void PauseUpdate(float dt);
	void EventUpdate(float dt);
	void BossUpdate(float dt);
	void EndingUpdate(float dt);
	void DeadUpdate(float dt);

	void Pause();
	void PauseMenu(float dt);
	void PhaseChange();

	void TimerFont();
	void PowerFont();
	void ScoreFont();
	void LifeFont();
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
