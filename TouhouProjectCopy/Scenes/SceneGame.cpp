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
#include "BulletEffect.h"

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

	poolEffect.OnCreate = [this](BulletEffect* bulletEffect)
	{
		bulletEffect->SetPool(&poolEffect);
	};
	
	{
		SpriteGo* leftBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		leftBar->sprite.setTextureRect(sf::IntRect(0, 0, 31, 479));// -695 115 810 - 467 540 73
		leftBar->sprite.setScale(1.f, FRAMEWORK.GetWindowSize().y / 479.f);
		leftBar->SetPosition(0.f, 0.f);
		leftBar->sortLayer = 102;

		SpriteGo* rightBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		rightBar->sprite.setTextureRect(sf::IntRect(32, 0, 223, 479));
		rightBar->sprite.setScale(1.5f, FRAMEWORK.GetWindowSize().y / 479.f);
		rightBar->SetPosition(FRAMEWORK.GetWindowSize().x - (223 * 1.5), 0.f);
		rightBar->sortLayer = 102;

		SpriteGo* topBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		topBar->sprite.setTextureRect(sf::IntRect(0, 480, 383, 16));
		topBar->SetPosition(31.f, 0.f);
		topBar->sprite.setScale(914.5f / 383.f, 2.5f);
		topBar->sortLayer = 102;

		SpriteGo* buttomBar = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		buttomBar->sprite.setTextureRect(sf::IntRect(0, 495, 383, 16));
		buttomBar->SetPosition(31.f, FRAMEWORK.GetWindowSize().y - 40.f);
		buttomBar->sprite.setScale(914.5f / 383.f, 2.5f);
		buttomBar->sortLayer = 102;

		SpriteGo* score = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		score->sprite.setTextureRect(sf::IntRect(277, 18, 55, 16));
		score->SetPosition(FRAMEWORK.GetWindowSize().x - 290.f, 90.f);
		score->sprite.setScale(1.5f, 1.5f);
		score->sortLayer = 103;

		SpriteGo* playerLife = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		playerLife->sprite.setTextureRect(sf::IntRect(270, 35, 62, 20));
		playerLife->SetPosition(FRAMEWORK.GetWindowSize().x-300.f, 130.f);
		playerLife->sprite.setScale(1.5f, 1.5f);
		playerLife->sortLayer = 103;

		SpriteGo* power = (SpriteGo*)AddGo(new SpriteGo("graphics/mainView.png"));
		power->sprite.setTextureRect(sf::IntRect(270, 57, 60, 20));
		power->SetPosition(FRAMEWORK.GetWindowSize().x - 300.f, 170.f);
		power->sprite.setScale(1.5f, 1.5f);
		power->sortLayer = 103;


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
			timer1->sortLayer = 103;

			timer2 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			timer2->sprite.setTextureRect(font[1]);
			timer2->SetPosition(FRAMEWORK.GetWindowSize().x - 400.f, 70.f);
			timer2->sprite.setScale(1.5f, 1.5f);
			timer2->SetOrigin(Origins::BC);
			timer2->sortLayer = 103;

			timer3 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			timer3->sprite.setTextureRect(font[11]);
			timer3->SetPosition(FRAMEWORK.GetWindowSize().x - 370.f, 70.f);
			timer3->sprite.setScale(1.5f, 1.5f);
			timer3->SetOrigin(Origins::BC);
			timer3->sortLayer = 103;

			timer4 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			timer4->sprite.setTextureRect(font[1]);
			timer4->SetPosition(FRAMEWORK.GetWindowSize().x - 360.f, 70.f);
			timer4->sprite.setScale(1.f, 1.f);
			timer4->SetOrigin(Origins::BC);
			timer4->sortLayer = 103;

			timer5 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			timer5->sprite.setTextureRect(font[1]);
			timer5->SetPosition(FRAMEWORK.GetWindowSize().x - 340.f, 70.f);
			timer5->sprite.setScale(1.0f, 1.0f);
			timer5->SetOrigin(Origins::BC);
			timer5->sortLayer = 103;
		}

		{
			score1 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			score1->sprite.setTextureRect(font[0]);
			score1->SetPosition(FRAMEWORK.GetWindowSize().x - 100.f, 115.f);
			score1->sprite.setScale(1.5f, 1.5f);
			score1->SetOrigin(Origins::BC);
			score1->sortLayer = 103;

			score2 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			score2->sprite.setTextureRect(font[0]);
			score2->SetPosition(FRAMEWORK.GetWindowSize().x - 120.f, 115.f);
			score2->sprite.setScale(1.5f, 1.5f);
			score2->SetOrigin(Origins::BC);
			score2->sortLayer = 103;

			score3 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			score3->sprite.setTextureRect(font[0]);
			score3->SetPosition(FRAMEWORK.GetWindowSize().x - 140.f, 115.f);
			score3->sprite.setScale(1.5f, 1.5f);
			score3->SetOrigin(Origins::BC);
			score3->sortLayer = 103;

			score4 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			score4->sprite.setTextureRect(font[0]);
			score4->SetPosition(FRAMEWORK.GetWindowSize().x - 160.f, 115.f);
			score4->sprite.setScale(1.5f, 1.5f);
			score4->SetOrigin(Origins::BC);
			score4->sortLayer = 103;

			score5 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			score5->sprite.setTextureRect(font[0]);
			score5->SetPosition(FRAMEWORK.GetWindowSize().x - 180.f, 115.f);
			score5->sprite.setScale(1.5f, 1.5f);
			score5->SetOrigin(Origins::BC);
			score5->sortLayer = 103;
		}

		{
			power1 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			power1->sprite.setTextureRect(font[0]);
			power1->SetPosition(FRAMEWORK.GetWindowSize().x - 180.f, 200.f);
			power1->sprite.setScale(1.5f, 1.5f);
			power1->SetOrigin(Origins::BC);
			power1->sortLayer = 103;

			power2 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			power2->sprite.setTextureRect(font[0]);
			power2->SetPosition(FRAMEWORK.GetWindowSize().x - 160.f, 200.f);
			power2->sprite.setScale(1.5f, 1.5f);
			power2->SetOrigin(Origins::BC);
			power2->sortLayer = 103;

			power3 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			power3->sprite.setTextureRect(font[11]);
			power3->SetPosition(FRAMEWORK.GetWindowSize().x - 140.f, 200.f);
			power3->sprite.setScale(1.5f, 1.5f);
			power3->SetOrigin(Origins::BC);
			power3->sortLayer = 103;

			power4 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			power4->sprite.setTextureRect(font[0]);
			power4->SetPosition(FRAMEWORK.GetWindowSize().x - 130.f, 200.f);
			power4->sprite.setScale(1.0f, 1.0f);
			power4->SetOrigin(Origins::BC);
			power4->sortLayer = 103;

			power5 = (SpriteGo*)AddGo(new SpriteGo("graphics/ascii.png"));
			power5->sprite.setTextureRect(font[0]);
			power5->SetPosition(FRAMEWORK.GetWindowSize().x - 120.f, 200.f);
			power5->sprite.setScale(1.0f, 1.0f);
			power5->SetOrigin(Origins::BC);
			power5->sortLayer = 103;
		}
	}


	pauseBackGround = (ShapeGo*)AddGo(new ShapeGo());
	pauseBackGround->SetSize(FRAMEWORK.GetWindowSize());
	pauseBackGround->SetColor(sf::Color(41, 28, 19, 200));
	pauseBackGround->sortLayer = 101;
	pauseBackGround->SetActive(false);
	
	pauseBar = (SpriteGo*)AddGo(new SpriteGo("graphics/pause.png"));
	pauseBar->sprite.setTextureRect(sf::IntRect(5, 1, 39, 206));
	pauseBar->SetOrigin(Origins::ML);
	pauseBar->SetPosition(175.f,450.f);
	pauseBar->sprite.setColor(sf::Color(255, 255, 255, 150));
	pauseBar->sprite.setScale(1.7f, 1.7f);
	pauseBar->sortLayer = 104;
	pauseBar->SetActive(false);

	pauseMenu = (SpriteGo*)AddGo(new SpriteGo("graphics/pause.png"));
	pauseMenu->sprite.setTextureRect(sf::IntRect(50, 4, 59, 27));
	pauseMenu->SetOrigin(Origins::ML);
	pauseMenu->SetPosition(150.f, 350.f);
	pauseMenu->sprite.setScale(2.f, 2.f);
	pauseMenu->sortLayer = 105;
	pauseMenu->SetActive(false);

	returnToGame = (SpriteGo*)AddGo(new SpriteGo("graphics/pause.png"));
	returnToGame->sprite.setTextureRect(sf::IntRect(51, 35, 138, 21));
	returnToGame->SetOrigin(Origins::ML);
	returnToGame->SetPosition(200.f, 450.f);
	returnToGame->sprite.setScale(2.f, 2.f);
	returnToGame->sortLayer = 105;
	returnToGame->SetActive(false);

	returnToTitle = (SpriteGo*)AddGo(new SpriteGo("graphics/pause.png"));
	returnToTitle->sprite.setTextureRect(sf::IntRect(50, 68, 109, 21));
	returnToTitle->SetOrigin(Origins::ML);
	returnToTitle->SetPosition(200.f, 500.f);
	returnToTitle->sprite.setScale(2.f, 2.f);
	returnToTitle->sortLayer = 105;
	returnToTitle->SetActive(false);

	giveUpToReplay = (SpriteGo*)AddGo(new SpriteGo("graphics/pause.png"));
	giveUpToReplay->sprite.setTextureRect(sf::IntRect(50, 99, 124, 22));
	giveUpToReplay->SetOrigin(Origins::ML);
	giveUpToReplay->SetPosition(200.f, 550.f);
	giveUpToReplay->sprite.setScale(2.f, 2.f);
	giveUpToReplay->sortLayer = 105;
	giveUpToReplay->SetActive(false);
	
	realyBar = (SpriteGo*)AddGo(new SpriteGo("graphics/pause.png"));
	realyBar->sprite.setTextureRect(sf::IntRect(5, 1, 39, 206));
	realyBar->SetOrigin(Origins::ML);
	realyBar->SetPosition(500.f, 450.f);
	realyBar->sprite.setColor(sf::Color(255, 255, 255, 150));
	realyBar->sprite.setScale(1.7f, 1.7f);
	realyBar->sortLayer = 104;
	realyBar->SetActive(false);

	realy = (SpriteGo*)AddGo(new SpriteGo("graphics/pause.png"));
	realy->sprite.setTextureRect(sf::IntRect(50, 163, 139, 22));
	realy->SetOrigin(Origins::ML);
	realy->SetPosition(475.f, 350.f);
	realy->sprite.setScale(2.f, 2.f);
	realy->sortLayer = 105;
	realy->SetActive(false);

	yes = (SpriteGo*)AddGo(new SpriteGo("graphics/pause.png"));
	yes->sprite.setTextureRect(sf::IntRect(160, 68, 56, 21));
	yes->SetOrigin(Origins::ML);
	yes->SetPosition(500.f, 450.f);
	yes->sprite.setColor(sf::Color(255, 255, 255, 255));
	yes->sprite.setScale(2.f, 2.f);
	yes->sortLayer = 105;
	yes->SetActive(false);

	no = (SpriteGo*)AddGo(new SpriteGo("graphics/pause.png"));
	no->sprite.setTextureRect(sf::IntRect(176, 99, 57, 21));
	no->SetOrigin(Origins::ML);
	no->SetPosition(500.f, 550.f);
	no->sprite.setColor(sf::Color(255, 255, 255, 150));
	no->sprite.setScale(2.f, 2.f);
	no->sortLayer = 105;
	no->SetActive(false);

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

		immortal = (SpriteGo*)AddGo(new SpriteGo("graphics/pl01c.png"));
		immortal->SetOrigin(Origins::MC);
		immortal->sortLayer = 3;
		immortal->sprite.setScale(0.3f, 0.3f);
		immortal->SetActive(false);

		player = (Player*)AddGo(new Player());
		player->SetGameView(gameViewSize);
		player->sortLayer = 2;
		player->SetImmortal(immortal);
		player->SetLife(2);
		player->SetHitBox(pHitbox);
		player->SetGrazeBox(grazeBox);
		player->SetGraze(graze);

		ending = (SpriteGo*)AddGo(new SpriteGo());
		ending->sprite.setScale(FRAMEWORK.GetWindowSize().x / 640.f, FRAMEWORK.GetWindowSize().y / 480.f);
		ending->sortLayer = 105;

		backGround = (SpriteGo*)AddGo(new SpriteGo("graphics/stage05a.png"));
		backGround->sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
		backGround->SetPosition(gameViewSize.left+(gameViewSize.width/2), 0.f);
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

		SpriteGo* phaseEffect = (SpriteGo*)AddGo(new SpriteGo("graphics/etama2.png"));
		phaseEffect->sprite.setTextureRect(sf::IntRect(128, 79, 128, 128));
		phaseEffect->SetOrigin(Origins::MC);
		phaseEffect->sortLayer = 1;
		phaseEffect->sortOrder = -1;
		phaseEffect->SetActive(false);

		boss = (Boss*)AddGo(new Boss());
		boss->SetGameView(gameViewSize);
		boss->SetPlayer(player);
		boss->SetHitBox(bHitbox);
		boss->SetPhaseEffect(phaseEffect);
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
			bullet->SetEffectPool(&poolEffect);
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
	poolEffect.Release();

	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneGame::Enter()
{
	Scene::Enter();

	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);
	uiView.setSize(size);
	uiView.setCenter(size.x / 2.f, size.y / 2.f);

	playing = true;
	phaseChange = false;
	scaleChange = false;
	pause = false;
	realyYN = false;
	endingScene = false;
	clear = false;
	endingAni.Stop();
	pauseMenuSelect = 0;
	realySelect = 0;

	pauseBackGround->SetActive(pause);
	pauseBar->SetActive(pause);
	pauseMenu->SetActive(pause);
	returnToGame->SetActive(pause);
	returnToTitle->SetActive(pause);
	giveUpToReplay->SetActive(pause);

	timer = 90.00f;
	life1->SetActive(true);
	life2->SetActive(true);

	player->Reset();
	boss->Reset();

	bossClear->SetActive(false);
	clearFailed->SetActive(false);

	se_Sound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/se_select00.wav"));
	se_pickSound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/se_ok00.wav"));
	se_pause.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/se_pause.wav"));

	backGround->textureId = ("graphics/stage05a.png");
	backGround->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/stage05a.png"));
	backGround->sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
	backGround->SetPosition(gameViewSize.left + (gameViewSize.width / 2), 0.f);
	backGround->sprite.setScale(7.f, 7.f);
	backGround->SetOrigin(Origins::MC);

	gameMusic.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/mantle.wav"));
	gameMusic.setLoop(true);
	gameMusic.play();
	gameMusic.setVolume(20);

	endingAni.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Ending.csv"));

	endingAni.SetTarget(&ending->sprite);
}

void SceneGame::Exit()
{
	ClearPool(poolHitBox);
	ClearPool(poolBullet);
	ClearPool(poolEffect);
	player->Reset();
	boss->Reset();
	gameMusic.stop();
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
	endingAni.Update(dt);

	if (playing)
	{
		Pause(pause);
		Realy(realyYN);

		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape) && !realyYN)
		{
			if (!pause)
			{
				se_pause.play();
			}
			pause = !pause;
		}

		if (pause)
		{
			if (!realyYN)
			{
				switch (pauseMenuSelect)
				{
				case 0:
					returnToGame->sprite.setColor(sf::Color(255, 255, 255, 255));
					returnToTitle->sprite.setColor(sf::Color(255, 255, 255, 150));
					giveUpToReplay->sprite.setColor(sf::Color(255, 255, 255, 150));
					if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up))
					{
						se_Sound.play();
						pauseMenuSelect = 2;
					}
					else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Down))
					{
						se_Sound.play();
						pauseMenuSelect = 1;
					}
					else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
					{
						se_pickSound.play();
						pause = !pause;
					}
					break;
				case 1:
					returnToGame->sprite.setColor(sf::Color(255, 255, 255, 150));
					returnToTitle->sprite.setColor(sf::Color(255, 255, 255, 255));
					giveUpToReplay->sprite.setColor(sf::Color(255, 255, 255, 150));
					if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up))
					{
						se_Sound.play();
						pauseMenuSelect = 0;
					}
					else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Down))
					{
						se_Sound.play();
						pauseMenuSelect = 2;
					}
					else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
					{
						se_pickSound.play();
						realyYN = !realyYN;
					}
					break;
				case 2:
					returnToGame->sprite.setColor(sf::Color(255, 255, 255, 150));
					returnToTitle->sprite.setColor(sf::Color(255, 255, 255, 150));
					giveUpToReplay->sprite.setColor(sf::Color(255, 255, 255, 255));
					if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up))
					{
						se_Sound.play();
						pauseMenuSelect = 1;
					}
					else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Down))
					{
						se_Sound.play();
						pauseMenuSelect = 0;
					}
					else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
					{
						se_pickSound.play();
						realyYN = !realyYN;
					}
					break;
				}
			}
			else if (realyYN)
			{
				switch (pauseMenuSelect)
				{
				case 1:
					returnToGame->sprite.setColor(sf::Color(255, 255, 255, 150));
					returnToTitle->sprite.setColor(sf::Color(255, 255, 255, 220));
					giveUpToReplay->sprite.setColor(sf::Color(255, 255, 255, 150));
					if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up) || INPUT_MGR.GetKeyDown(sf::Keyboard::Down))
					{
						se_Sound.play();
						switch (realySelect)
						{
						case 0:
							realySelect = 1;
							yes->sprite.setColor(sf::Color(255, 255, 255, 150));
							no->sprite.setColor(sf::Color(255, 255, 255, 255));

							break;
						case 1:
							realySelect = 0;
							yes->sprite.setColor(sf::Color(255, 255, 255, 255));
							no->sprite.setColor(sf::Color(255, 255, 255, 150));
							break;
						}
					}
					else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
					{
						se_pickSound.play();
						switch (realySelect)
						{
						case 0:
							realyYN = !realyYN;
							pause = !pause;
							SCENE_MGR.ChangeScene(SceneId::Title);
							break;
						case 1:
							realyYN = !realyYN;
							realySelect = 0;
							break;
						}
					}
					else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
					{
						se_pickSound.play();
						realyYN = !realyYN;
						realySelect = 0;
					}
					break;
				case 2:
					returnToGame->sprite.setColor(sf::Color(255, 255, 255, 150));
					returnToTitle->sprite.setColor(sf::Color(255, 255, 255, 150));
					giveUpToReplay->sprite.setColor(sf::Color(255, 255, 255, 220));
					if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up) || INPUT_MGR.GetKeyDown(sf::Keyboard::Down))
					{
						se_Sound.play();
						switch (realySelect)
						{
						case 0:
							realySelect = 1;
							yes->sprite.setColor(sf::Color(255, 255, 255, 150));
							no->sprite.setColor(sf::Color(255, 255, 255, 255));
							break;
						case 1:
							realySelect = 0;
							yes->sprite.setColor(sf::Color(255, 255, 255, 255));
							no->sprite.setColor(sf::Color(255, 255, 255, 150));
							break;
						}
					}
					else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
					{
						se_pickSound.play();
						switch (realySelect)
						{
						case 0:
							realyYN = !realyYN;
							pause = !pause;
							SCENE_MGR.ChangeScene(SceneId::Game);
							break;
						case 1:
							realyYN = !realyYN;
							realySelect = 0;
							break;
						}
					}
					else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
					{
						se_pickSound.play();
						realySelect = 0;
						realyYN = !realyYN;
					}
					break;
				}
			}
			dt = 0;
		}
		if(!phaseChange)
		{
			timer -= dt;

			backGround->sprite.rotate(20 * dt);
			graze->sprite.rotate(720 * dt);

			if (boss->GetBossHp() <= 0 && !boss->GetPhase())
			{
				phaseChange = true;
				changeTimer = 0.f;
				if (!poolBullet.GetUseList().empty())
				{
					for (auto obj : poolBullet.GetUseList())
					{
						RemoveGo(obj);
					}
				}
				if (!poolHitBox.GetUseList().empty())
				{
					for (auto obj : poolHitBox.GetUseList())
					{
						RemoveGo(obj);
					}
				}
				if (!poolEffect.GetUseList().empty())
				{
					for (auto obj : poolEffect.GetUseList())
					{
						RemoveGo(obj);
					}
				}

				player->SetChangePhase(true);
				boss->SetPhase(true);
				boss->SetSpeed(0.f);
				boss->SetDirX(0.f);
				pHitbox->SetActive(false);
				bHitbox->SetActive(false);
				graze->SetActive(false);
				grazeBox->SetActive(false);
			}
			else if (boss->GetBossHp() <= 0 && boss->GetPhase())
			{
				bossClear->SetActive(true);
				playing = false;
				boss->SetActive(false);
				boss->SetPhaseEffect(false);
				boss->SetAction(true);
				clear = true;
				player->SetPlaying(playing);
			}
			if (player->GetLife() < 1)
			{
				playing = false;
				player->SetPlaying(playing);
				clearFailed->SetActive(true);
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
		else if (phaseChange)
		{
			timer = 90.f;

			changeTimer += dt;
			if (!scaleChange)
			{
				backGround->sprite.setColor(sf::Color(255, 255, 255, (1.f - (changeTimer / changeClearTime)) * 255));
			}
			else if (scaleChange)
			{
				boss->SetHP(boss->GetBossHp() + (changeTimer / changeClearTime) *
					(boss->GetBossMaxHp() - boss->GetBossHp()));
				backGround->sprite.setScale(backGround->sprite.getScale() +
					(changeTimer / changeClearTime) * 
					(backGroundScale - backGround->sprite.getScale()));
			}
			if (changeClearTime <=changeTimer)
			{
				if (!scaleChange)
				{
					scaleChange = true;
					backGround->textureId = ("graphics/stage06c.png");
					backGround->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/stage06c.png"));
					backGround->sprite.setColor(sf::Color(255, 255, 255, 255));
					backGround->sprite.setTextureRect(sf::IntRect(0, 0, 512, 512));
					backGround->sprite.setScale(7.f, 7.f);
					backGround->SetOrigin(Origins::MC);

					pHitbox->SetActive(true);
					bHitbox->SetActive(true);
					graze->SetActive(true);
					grazeBox->SetActive(true);
					boss->SetPhaseEffect(true);
					changeTimer = 0.f;
				}
				else if (scaleChange)
				{
					gameMusic.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/Nuclear_Fusion.wav"));
					gameMusic.setLoop(true);
					gameMusic.play();
					gameMusic.setVolume(20);

					phaseChange = false;
					player->SetChangePhase(false);
					boss->SetAction(false);
				}
			}
		}
	}
	else if (!playing)
	{
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter)&&boss->GetPhase()&&!endingScene&&clear)
		{
			gameMusic.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/comeBackHome.wav"));
			gameMusic.setLoop(true);
			gameMusic.play();
			gameMusic.setVolume(30);
			endingAni.Play("Ending");
			endingScene = true;
		}
		else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter) && boss->GetPhase() && endingScene && clear)
		{
			SCENE_MGR.ChangeScene(SceneId::Title);
		}
		else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter) && !clear)
		{
			SCENE_MGR.ChangeScene(SceneId::Title);
		}
	}

	bossHp->SetSize({ boss->GetBossHp() * (800.f /boss->GetBossMaxHp()) ,3.f });
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::GetBullet(Bullet*& bullet)
{
	bullet = poolBullet.Get();
}

void SceneGame::Pause(bool pause)
{
		pauseBackGround->SetActive(pause);
		pauseBar->SetActive(pause);
		pauseMenu->SetActive(pause);
		returnToGame->SetActive(pause);
		returnToTitle->SetActive(pause);
		giveUpToReplay->SetActive(pause);
}

void SceneGame::Realy(bool realyYN)
{
	realyBar->SetActive(realyYN);
	realy->SetActive(realyYN);
	yes->SetActive(realyYN);
	no->SetActive(realyYN);
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
