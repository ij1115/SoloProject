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

	gameViewSize.left = -FRAMEWORK.GetWindowSize().x / 2 + 31.f;
	gameViewSize.top = -FRAMEWORK.GetWindowSize().y / 2 + 40.f;
	gameViewSize.width = 914.5f;
	gameViewSize.height = 640.f;
	
	poolBullet.OnCreate = [this](Bullet* bullet)
	{
		bullet->SetPool(&poolBullet);
		bullet->SetGameView(gameViewSize);
	};
	poolHitBox.OnCreate = [this](ShapeGo* hitbox)
	{
		hitbox->SetPool(&poolHitBox);
	};

	SpriteGo* leftBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
	leftBar->sprite.setTextureRect(sf::IntRect(0, 0, 31, 479));// -695 115 810 - 467 540 73
	leftBar->sprite.setScale(1.f, FRAMEWORK.GetWindowSize().y / 479.f);
	leftBar->SetPosition(0.f, 0.f);
	leftBar->sortLayer = 101;

	SpriteGo* rightBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
	rightBar->sprite.setTextureRect(sf::IntRect(32, 0, 223, 479));
	rightBar->sprite.setScale(1.5f, FRAMEWORK.GetWindowSize().y / 479.f);
	rightBar->SetPosition(FRAMEWORK.GetWindowSize().x-(223*1.5), 0.f);
	rightBar->sortLayer = 101;

	SpriteGo* topBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
	topBar->sprite.setTextureRect(sf::IntRect(0, 480, 383, 16));
	topBar->SetPosition(31.f, 0.f);
	topBar->sprite.setScale(914.5f/383.f, 2.5f);
	topBar->sortLayer = 101;

	SpriteGo* buttomBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
	buttomBar->sprite.setTextureRect(sf::IntRect(0, 495, 383, 16));
	buttomBar->SetPosition(31.f, FRAMEWORK.GetWindowSize().y - 40.f);
	buttomBar->sprite.setScale(914.5f / 383.f, 2.5f);
	buttomBar->sortLayer = 101;

	ShapeGo* pHitbox = poolHitBox.Get();
	pHitbox->SetHitBoxSize({ 5.f,5.f });
	pHitbox->SetHitBoxFillColor(sf::Color::Transparent);
	pHitbox->SetHitBoxOutLineColor(sf::Color::Red);
	pHitbox->SetHitBoxOutLineThickness(1);
	pHitbox->SetOrigin(Origins::MC);
	pHitbox->sortLayer = 5;
	pHitbox->SetType(0);
	AddGo(pHitbox);


	Player* player = (Player*)AddGo(new Player());
	player->SetGameView(gameViewSize);
	player->sortLayer = 1;
	player->SetHitBox(pHitbox);

	backGround = (SpriteGo*)AddGo(new SpriteGo("graphics/stage05a.png"));
	backGround->sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
	backGround->SetPosition(-200.f, 0.f);
	backGround->sprite.setScale(7.f, 7.f);
	backGround->SetOrigin(Origins::MC);
	backGround->sortLayer = -1;

	ShapeGo* bHitbox = poolHitBox.Get();
	bHitbox->SetHitBoxSize({ 62.f,80.f });
	bHitbox->SetHitBoxFillColor(sf::Color::Transparent);
	bHitbox->SetHitBoxOutLineColor(sf::Color::Red);
	bHitbox->SetHitBoxOutLineThickness(1);
	bHitbox->SetOrigin(Origins::MC);
	bHitbox->sortLayer = 5;
	bHitbox->SetType(1);
	AddGo(bHitbox);

	Boss* boss = (Boss*)AddGo(new Boss());
	boss->SetGameView(gameViewSize);
	boss->SetPlayer(player);
	boss->SetHitBox(bHitbox);

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
	uiView.setSize(size);
	uiView.setCenter(size.x/2.f,size.y/2.f);

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