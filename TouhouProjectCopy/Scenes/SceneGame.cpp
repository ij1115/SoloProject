#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "GameObject.h"
#include "Framework.h"
#include "HitboxGo.h"
#include "UiButton.h"
#include "Boss.h"
#include "ShapeGo.h"
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
	
	poolHitBox.OnCreate = [this](HitboxGo* hitbox)
	{
		hitbox->SetPool(&poolHitBox);
	};
	poolHitBox.Init();

	{
		SpriteGo* leftBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		leftBar->sprite.setTextureRect(sf::IntRect(0, 0, 31, 479));// -695 115 810 - 467 540 73
		leftBar->sprite.setScale(1.f, FRAMEWORK.GetWindowSize().y / 479.f);
		leftBar->SetPosition(0.f, 0.f);
		leftBar->sortLayer = 101;

		SpriteGo* rightBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		rightBar->sprite.setTextureRect(sf::IntRect(32, 0, 223, 479));
		rightBar->sprite.setScale(1.5f, FRAMEWORK.GetWindowSize().y / 479.f);
		rightBar->SetPosition(FRAMEWORK.GetWindowSize().x - (223 * 1.5), 0.f);
		rightBar->sortLayer = 101;

		SpriteGo* topBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		topBar->sprite.setTextureRect(sf::IntRect(0, 480, 383, 16));
		topBar->SetPosition(31.f, 0.f);
		topBar->sprite.setScale(914.5f / 383.f, 2.5f);
		topBar->sortLayer = 101;

		SpriteGo* buttomBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		buttomBar->sprite.setTextureRect(sf::IntRect(0, 495, 383, 16));
		buttomBar->SetPosition(31.f, FRAMEWORK.GetWindowSize().y - 40.f);
		buttomBar->sprite.setScale(914.5f / 383.f, 2.5f);
		buttomBar->sortLayer = 101;

		SpriteGo* score = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		score->sprite.setTextureRect(sf::IntRect(277, 18, 55, 16));
		score->SetPosition(FRAMEWORK.GetWindowSize().x - 290.f, 90.f);
		score->sprite.setScale(1.5f, 1.5f);
		score->sortLayer = 102;

		SpriteGo* playerLife = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		playerLife->sprite.setTextureRect(sf::IntRect(270, 35, 62, 20));
		playerLife->SetPosition(FRAMEWORK.GetWindowSize().x-300.f, 130.f);
		playerLife->sprite.setScale(1.5f, 1.5f);
		playerLife->sortLayer = 102;

		SpriteGo* power = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		power->sprite.setTextureRect(sf::IntRect(270, 57, 60, 20));
		power->SetPosition(FRAMEWORK.GetWindowSize().x - 300.f, 170.f);
		power->sprite.setScale(1.5f, 1.5f);
		power->sortLayer = 102;


		for (int i = 0; i < 12; ++i)
		{
			sf::IntRect num = { 16*i, 216, 16, 16 };
			font.push_back(num);
		}

		{
			timer1 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			timer1->sprite.setTextureRect(font[0]);
			timer1->SetPosition(FRAMEWORK.GetWindowSize().x - 420.f, 70.f);
			timer1->sprite.setScale(1.5f, 1.5f);
			timer1->SetOrigin(Origins::BC);
			timer1->sortLayer = 102;

			timer2 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			timer2->sprite.setTextureRect(font[1]);
			timer2->SetPosition(FRAMEWORK.GetWindowSize().x - 400.f, 70.f);
			timer2->sprite.setScale(1.5f, 1.5f);
			timer2->SetOrigin(Origins::BC);
			timer2->sortLayer = 102;

			timer3 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			timer3->sprite.setTextureRect(font[11]);
			timer3->SetPosition(FRAMEWORK.GetWindowSize().x - 370.f, 70.f);
			timer3->sprite.setScale(1.5f, 1.5f);
			timer3->SetOrigin(Origins::BC);
			timer3->sortLayer = 102;

			timer4 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			timer4->sprite.setTextureRect(font[1]);
			timer4->SetPosition(FRAMEWORK.GetWindowSize().x - 360.f, 70.f);
			timer4->sprite.setScale(1.f, 1.f);
			timer4->SetOrigin(Origins::BC);
			timer4->sortLayer = 102;

			timer5 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			timer5->sprite.setTextureRect(font[1]);
			timer5->SetPosition(FRAMEWORK.GetWindowSize().x - 340.f, 70.f);
			timer5->sprite.setScale(1.0f, 1.0f);
			timer5->SetOrigin(Origins::BC);
			timer5->sortLayer = 102;
		}

		{
			score1 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			score1->sprite.setTextureRect(font[0]);
			score1->SetPosition(FRAMEWORK.GetWindowSize().x - 100.f, 115.f);
			score1->sprite.setScale(1.5f, 1.5f);
			score1->SetOrigin(Origins::BC);
			score1->sortLayer = 102;

			score2 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			score2->sprite.setTextureRect(font[0]);
			score2->SetPosition(FRAMEWORK.GetWindowSize().x - 120.f, 115.f);
			score2->sprite.setScale(1.5f, 1.5f);
			score2->SetOrigin(Origins::BC);
			score2->sortLayer = 102;

			score3 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			score3->sprite.setTextureRect(font[0]);
			score3->SetPosition(FRAMEWORK.GetWindowSize().x - 140.f, 115.f);
			score3->sprite.setScale(1.5f, 1.5f);
			score3->SetOrigin(Origins::BC);
			score3->sortLayer = 102;

			score4 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			score4->sprite.setTextureRect(font[0]);
			score4->SetPosition(FRAMEWORK.GetWindowSize().x - 160.f, 115.f);
			score4->sprite.setScale(1.5f, 1.5f);
			score4->SetOrigin(Origins::BC);
			score4->sortLayer = 102;

			score5 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			score5->sprite.setTextureRect(font[0]);
			score5->SetPosition(FRAMEWORK.GetWindowSize().x - 180.f, 115.f);
			score5->sprite.setScale(1.5f, 1.5f);
			score5->SetOrigin(Origins::BC);
			score5->sortLayer = 102;
		}

		{
			power1 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			power1->sprite.setTextureRect(font[0]);
			power1->SetPosition(FRAMEWORK.GetWindowSize().x - 180.f, 200.f);
			power1->sprite.setScale(1.5f, 1.5f);
			power1->SetOrigin(Origins::BC);
			power1->sortLayer = 102;

			power2 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			power2->sprite.setTextureRect(font[0]);
			power2->SetPosition(FRAMEWORK.GetWindowSize().x - 160.f, 200.f);
			power2->sprite.setScale(1.5f, 1.5f);
			power2->SetOrigin(Origins::BC);
			power2->sortLayer = 102;

			power3 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			power3->sprite.setTextureRect(font[11]);
			power3->SetPosition(FRAMEWORK.GetWindowSize().x - 140.f, 200.f);
			power3->sprite.setScale(1.5f, 1.5f);
			power3->SetOrigin(Origins::BC);
			power3->sortLayer = 102;

			power4 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			power4->sprite.setTextureRect(font[0]);
			power4->SetPosition(FRAMEWORK.GetWindowSize().x - 130.f, 200.f);
			power4->sprite.setScale(1.0f, 1.0f);
			power4->SetOrigin(Origins::BC);
			power4->sortLayer = 102;

			power5 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			power5->sprite.setTextureRect(font[0]);
			power5->SetPosition(FRAMEWORK.GetWindowSize().x - 120.f, 200.f);
			power5->sprite.setScale(1.0f, 1.0f);
			power5->SetOrigin(Origins::BC);
			power5->sortLayer = 102;
		}
	}

	{
		life1 = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		life1->sprite.setTextureRect(sf::IntRect(464, 2, 16, 15));
		life1->SetOrigin(Origins::MC);
		life1->SetPosition(FRAMEWORK.GetWindowSize().x - 180.f, 145.f);
		life1->sprite.setScale(2.f, 2.f);
		life1->sortLayer = 102;
		life1->SetActive(true);

		life2 = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		life2->sprite.setTextureRect(sf::IntRect(464, 2, 16, 15));
		life2->SetOrigin(Origins::MC);
		life2->SetPosition(FRAMEWORK.GetWindowSize().x - 140.f, 145.f);
		life2->sprite.setScale(2.f, 2.f);
		life2->sortLayer = 102;
		life2->SetActive(true);



		bossClear = (SpriteGo*)AddGo(new SpriteGo("graphics/front01.png"));
		bossClear->sprite.setTextureRect(sf::IntRect(15, 9, 223, 32));
		bossClear->SetOrigin(Origins::MC);
		bossClear->SetPosition(488.25f, FRAMEWORK.GetWindowSize().y / 2);
		bossClear->sprite.setScale(2.f, 2.f);
		bossClear->sortLayer = 102;
		bossClear->SetActive(false);

		clearFailed = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		clearFailed->sprite.setTextureRect(sf::IntRect(330, 388, 79, 26));
		clearFailed->SetOrigin(Origins::MC);
		clearFailed->SetPosition(488.25f, FRAMEWORK.GetWindowSize().y / 2);
		clearFailed->sprite.setScale(5.f, 5.f);
		clearFailed->sortLayer = 102;
		clearFailed->SetActive(false);


		bossName = (SpriteGo*)AddGo(new SpriteGo("graphics/ename.png"));
		bossName->sprite.setTextureRect(sf::IntRect(0, 95, 69, 10));
		bossName->SetPosition(41.f, 60.f);
		bossName->sprite.setScale(2.f, 2.f);
		bossName->sortLayer = 101;


		pHitbox = (HitboxGo*)AddGo(new HitboxGo());
		pHitbox->SetHitBoxSize(1.f);
		pHitbox->SetHitBoxFillColor(sf::Color::Transparent);
		pHitbox->SetHitBoxOutLineColor(sf::Color::Red);
		pHitbox->SetHitBoxOutLineThickness(1);
		pHitbox->SetOrigin(Origins::MC);
		pHitbox->sortLayer = -2;
		pHitbox->SetType(0);

		grazeBox = (HitboxGo*)AddGo(new HitboxGo());
		grazeBox->SetHitBoxSize(45.f);
		grazeBox->SetHitBoxFillColor(sf::Color::Transparent);
		grazeBox->SetHitBoxOutLineColor(sf::Color::Red);
		grazeBox->SetHitBoxOutLineThickness(1);
		grazeBox->SetOrigin(Origins::MC);
		grazeBox->sortLayer = -2;
		grazeBox->SetType(0);

		graze = (SpriteGo*)AddGo(new SpriteGo("graphics/pl00b.png"));
		graze->sprite.setTextureRect(sf::IntRect(0, 195, 64, 64));
		graze->SetOrigin(Origins::MC);
		graze->sortLayer = -2;

		player = (Player*)AddGo(new Player());
		player->SetGameView(gameViewSize);
		player->sortLayer = 2;
		player->SetLife(2);
		player->SetHitBox(pHitbox);
		player->SetGrazeBox(grazeBox);
		player->SetGraze(graze);

		backGround = (SpriteGo*)AddGo(new SpriteGo("graphics/stage05a.png"));
		backGround->sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
		backGround->SetPosition(-200.f, 0.f);
		backGround->sprite.setScale(7.f, 7.f);
		backGround->SetOrigin(Origins::MC);
		backGround->sortLayer = -1;

		bHitbox = (HitboxGo*)AddGo(new HitboxGo());
		bHitbox->SetHitBoxSize(31.f);
		bHitbox->SetHitBoxFillColor(sf::Color::Transparent);
		bHitbox->SetHitBoxOutLineColor(sf::Color::Red);
		bHitbox->SetHitBoxOutLineThickness(1);
		bHitbox->SetOrigin(Origins::MC);
		bHitbox->sortLayer = -2;
		bHitbox->SetType(1);

		boss = (Boss*)AddGo(new Boss());
		boss->SetGameView(gameViewSize);
		boss->SetPlayer(player);
		boss->SetHitBox(bHitbox);
		boss->sortLayer = 1;

		bossHp = (ShapeGo*)AddGo(new ShapeGo());
		bossHp->SetPosition(41.f, 55.f);
		bossHp->sortLayer = 101;
		bossHp->SetOrigin(Origins::ML);

		poolBullet.OnCreate = [this](Bullet* bullet)
		{
			bullet->SetPool(&poolBullet);
			bullet->SetGameView(gameViewSize);
			bullet->SetHitBoxPool(&poolHitBox);
			bullet->SetBoss(boss);
			bullet->SetPlayer(player);
		};
		poolBullet.Init();
	}

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	poolBullet.Release();
	poolHitBox.Release();

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

	playing = true;
	player->SetLife(2);
	player->SetPlaying(playing);
	bossClear->SetActive(false);
	clearFailed->SetActive(false);
	timer = 90.00f;
	player->SetScore(0);
	player->SetPower(0.f);
	life1->SetActive(true);
	life2->SetActive(true);

	Scene::Enter();
}

void SceneGame::Exit()
{
	ClearPool(poolHitBox);
	ClearPool(poolBullet);
	player->Reset();
	boss->Reset();
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	if (player->GetLife() == 1 && life2->GetActive())
	{
		life2->SetActive(false);
	}
	else if (player->GetLife() == 0 && life1->GetActive())
	{
		life1->SetActive(false);
	}

	Scene::Update(dt);

	if (playing)
	{
		timer -= dt;

		backGround->sprite.rotate(20 * dt);
		graze->sprite.rotate(720 * dt);

		if (player->GetLife() < 1)
		{
			playing = false;
			player->SetPlaying(playing);
			clearFailed->SetActive(true);
		}
		else if (boss->GetBossHp() == 0)
		{
			bossClear->SetActive(true);
			playing = false;
			boss->SetActive(false);
			player->SetPlaying(playing);
		}
		else if (timer < 0.f)
		{
			playing = false;
			player->SetPlaying(playing);
			clearFailed->SetActive(true);
		}

		TimerFont();
		ScoreFont();
		PowerFont();
	}
	else if (!playing)
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneId::Game);
		}
	}

	bossHp->SetSize({ boss->GetBossHp() * (800.f /boss->GetBossMaxHp()) ,3.f });


	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}


}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::GetBullet(Bullet*& bullet)
{
	bullet = poolBullet.Get();
}

void SceneGame::TimerFont()
{
	int getHigh = static_cast<int>(timer);
	float timerLow = timer - static_cast<float>(getHigh);
	int getLow = static_cast<float>(static_cast<int>(timerLow * 100));


	num1 = getHigh / 10;
	num2 = getHigh % 10;
	num3 = getLow / 10;
	num4 = getLow % 10;

	timer1->sprite.setTextureRect(font[num1]);
	timer2->sprite.setTextureRect(font[num2]);
	timer4->sprite.setTextureRect(font[num3]);
	timer5->sprite.setTextureRect(font[num4]);
}
void SceneGame::PowerFont()
{
	int getHigh = static_cast<int>(player->GetPower());
	float timerLow = player->GetPower() - static_cast<float>(getHigh);
	int getLow = static_cast<float>(static_cast<int>(timerLow * 100));


	num1 = getHigh / 10;
	num2 = getHigh % 10;
	num3 = getLow / 10;
	num4 = getLow % 10;

	power1->sprite.setTextureRect(font[num1]);
	power2->sprite.setTextureRect(font[num2]);
	power4->sprite.setTextureRect(font[num3]);
	power5->sprite.setTextureRect(font[num4]);
}
void SceneGame::ScoreFont()
{
	num1 = player->GetScore() % 10;
	num2 = (player->GetScore() / 10) % 10;
	num3 = (player->GetScore() / 100) % 10;
	num4 = (player->GetScore() / 1000) % 10;
	num5 = (player->GetScore() / 10000) % 10;
	
	score1->sprite.setTextureRect(font[num1]);
	score2->sprite.setTextureRect(font[num2]);
	score3->sprite.setTextureRect(font[num3]);
	score4->sprite.setTextureRect(font[num4]);
	score5->sprite.setTextureRect(font[num5]);
}
