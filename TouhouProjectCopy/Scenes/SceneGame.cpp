#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "GameObject.h"
#include "Framework.h"
#include "ShapeGo.h"
#include "UiButton.h"
#include "Boss.h"
#include "Bullet.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
	resourceListPath = "scripts/SceneGameResourceList.csv";
}

void SceneGame::Init()
{
	Release();
	
	poolBullet.OnCreate = [this](Bullet* bullet)
	{
		bullet->SetPool(&poolBullet);
	};

	SpriteGo* leftBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
	leftBar->sprite.setTextureRect(sf::IntRect(0, 0, 31, 479));// -695 115 810 - 467 540 73
	leftBar->sprite.setScale(1.f, FRAMEWORK.GetWindowSize().y / 479.f);
	leftBar->SetPosition(0.f, 0.f);
	leftBar->sortLayer = 101;

	SpriteGo* rightBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png", "sibal"));
	rightBar->sprite.setTextureRect(sf::IntRect(32, 0, 223, 479));
	rightBar->sprite.setScale((1000.f - 509.75f) / 223.f, FRAMEWORK.GetWindowSize().y / 479.f);
	rightBar->SetPosition(509.75f, 0.f);
	rightBar->sortLayer = 101;

	SpriteGo* topBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
	topBar->sprite.setTextureRect(sf::IntRect(0, 480, 383, 16));
	topBar->SetPosition(31.f, 0.f);
	topBar->sprite.setScale(1.25f, 2.5f);
	topBar->sortLayer = 101;

	SpriteGo* buttomBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
	buttomBar->sprite.setTextureRect(sf::IntRect(0, 495, 383, 16));
	buttomBar->SetPosition(31.f, 1000.f - 40.f);
	buttomBar->sprite.setScale(1.25f, 2.5f);
	buttomBar->sortLayer = 101;

	Player* player = (Player*)AddGo(new Player());
	player->sortLayer = 1;

	backGround = (SpriteGo*)AddGo(new SpriteGo("graphics/stage05a.png"));
	backGround->sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
	backGround->SetPosition(-200.f, 0.f);
	backGround->sprite.setScale(7.f, 7.f);
	backGround->SetOrigin(Origins::MC);
	backGround->sortLayer = -1;
	
	std::cout << backGround->GetPosition().x << std::endl;
	std::cout << backGround->GetPosition().y << std::endl;
	// -695 115 810 - 467 540 73



	Boss* boss = (Boss*)AddGo(new Boss());

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	backGround->sprite.rotate(20 * dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::GetBullet(Bullet*& bullet)
{
	bullet = poolBullet.Get();
}