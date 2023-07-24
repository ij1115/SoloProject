#pragma once
#include "Scene.h"

class SpriteGo;

class SceneTitle : public Scene
{
protected:
	bool change = false;
	float timer = 0.f;

	int select = 0;

	SpriteGo* backGround;
	SpriteGo* logo;
	SpriteGo* loading_kor;
	SpriteGo* loading_Eng;


	std::vector<sf::IntRect> buttonActive;
	sf::Sound titleMusic;
	sf::Sound se_Sound;
	sf::Sound se_pickSound;

	SpriteGo* startButton;
	SpriteGo* exitButton;
public:
	SceneTitle();
	virtual ~SceneTitle() override = default;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

