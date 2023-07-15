#pragma once
#include "Scene.h"
#include "ObjectPool.h"

class SpriteGo;
class Player;
class Bullet;

class SceneGame : public Scene
{
protected:
	Player* player;
	SpriteGo* backGround;

	sf::FloatRect gameViewSize;

	ObjectPool<Bullet> poolBullet;
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
};

