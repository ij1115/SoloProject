#include "stdafx.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"


SceneTitle::SceneTitle() : Scene(SceneId::Title)
{
	resourceListPath = "scripts/SceneTitleResourceList.csv";
}

void SceneTitle::Init()
{
	Release();
	auto size = FRAMEWORK.GetWindowSize();

	loading_kor = (SpriteGo*)AddGo(new SpriteGo("graphics/loading.png"));
	loading_kor->sprite.setTextureRect(sf::IntRect(8, 3, 111, 25));
	loading_kor->sprite.setScale(1.5f, 1.5f);
	loading_kor->SetOrigin(Origins::MC);
	loading_kor->SetPosition(size.x-200.f,size.y-100.f);
	loading_kor->sortLayer = 105;
	loading_kor->SetActive(false);

	loading_Eng = (SpriteGo*)AddGo(new SpriteGo("graphics/loading.png"));
	loading_Eng->sprite.setTextureRect(sf::IntRect(16, 40, 102, 20));
	loading_Eng->sprite.setScale(1.5f, 1.5f);
	loading_Eng->SetOrigin(Origins::MC);
	loading_Eng->SetPosition(size.x - 150.f, size.y - 50.f);
	loading_Eng->sortLayer = 105;
	loading_Eng->SetActive(false);


	backGround = (SpriteGo*)AddGo(new SpriteGo("graphics/title00a.png"));
	backGround->sprite.setScale(size.x / 640.f, size.y / 480.f);
	backGround->SetPosition(0.f, 0.f);
	backGround->SetOrigin(Origins::TL);
	backGround->sprite.setColor(sf::Color(255, 255, 255, 0));
	backGround->sortLayer = 101;
	
	logo = (SpriteGo*)AddGo(new SpriteGo("graphics/title_logo.png"));
	logo->sprite.setTextureRect(sf::IntRect(14, 145, 605, 33));
	logo->sprite.setScale(1.5f, 1.5f);
	logo->SetOrigin(Origins::MC);
	logo->SetPosition(size.x/2, 400.f);
	logo->sortLayer = 103;
	logo->sprite.rotate(-20);

	SpriteGo* logo_tou = (SpriteGo*)AddGo(new SpriteGo("graphics/title_logo.png"));
	logo_tou->sprite.setTextureRect(sf::IntRect(13, 11, 108, 104));
	logo_tou->SetPosition(500.f, 20.f);
	logo_tou->sprite.setScale(1.5f, 1.5f);
	logo_tou->sortLayer = 102;

	SpriteGo* logo_hou = (SpriteGo*)AddGo(new SpriteGo("graphics/title_logo.png"));
	logo_hou->sprite.setTextureRect(sf::IntRect(146, 14, 63, 62));
	logo_hou->SetPosition(650.f, 150.f);
	logo_hou->sprite.setScale(1.5f, 1.5f);
	logo_hou->sortLayer = 102;

	SpriteGo* logo_chi = (SpriteGo*)AddGo(new SpriteGo("graphics/title_logo.png"));
	logo_chi->sprite.setTextureRect(sf::IntRect(241, 17, 100, 103));
	logo_chi->SetPosition(550.f, 250.f);
	logo_chi->sprite.setScale(1.5f, 1.5f);
	logo_chi->sortLayer = 102;

	SpriteGo* logo_rei = (SpriteGo*)AddGo(new SpriteGo("graphics/title_logo.png"));
	logo_rei->sprite.setTextureRect(sf::IntRect(401, 13, 87, 97));
	logo_rei->SetPosition(700.f, 400.f);
	logo_rei->sprite.setScale(1.5f, 1.5f);
	logo_rei->sortLayer = 102;

	SpriteGo* logo_den = (SpriteGo*)AddGo(new SpriteGo("graphics/title_logo.png"));
	logo_den->sprite.setTextureRect(sf::IntRect(524, 12, 68, 65));
	logo_den->SetPosition(650.f, 530.f);
	logo_den->sprite.setScale(1.8f, 1.8f);
	logo_den->sortLayer = 102;

	sf::IntRect button = { 130, 4, 81, 24 };
	buttonActive.push_back(button);

	button = { 2,4,81,24 };
	buttonActive.push_back(button);

	button = { 131,228,37,25};
	buttonActive.push_back(button);

	button = { 3,228,37,25 };
	buttonActive.push_back(button);

	startButton = (SpriteGo*)AddGo(new SpriteGo("graphics/KoreanUi.png"));
	startButton->sprite.setTextureRect(sf::IntRect(2, 4, 81, 24));
	startButton->sprite.setScale(2.f, 2.f);
	startButton->SetPosition(1000.f, 530.f);
	startButton->sortLayer = 103;

	exitButton = (SpriteGo*)AddGo(new SpriteGo("graphics/KoreanUi.png"));
	exitButton->sprite.setTextureRect(sf::IntRect(131, 228, 37, 25));
	exitButton->sprite.setScale(2.f, 2.f);
	exitButton->SetPosition(1005.f, 580.f);
	exitButton->sortLayer = 103;
}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneTitle::Enter()
{

	Scene::Enter();

	auto size = FRAMEWORK.GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);
	uiView.setSize(size);
	uiView.setCenter(size.x / 2.f, size.y / 2.f);

	for (auto go : gameObjects)
	{
		go->SetActive(true);
	}

	backGround->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/title00a.png"));
	se_Sound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/se_select00.wav"));
	se_pickSound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/se_ok00.wav"));
	titleMusic.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/title.wav"));
	titleMusic.setLoop(true);
	titleMusic.play();
	titleMusic.setVolume(20);
	change = false;
	loading_kor->SetActive(false);
	loading_Eng->SetActive(false);
}

void SceneTitle::Exit()
{
	Scene::Exit();
	titleMusic.stop();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (change)
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}

	if(timer<0.5f)
	{
		timer += dt;
	}

	backGround->sprite.setColor(sf::Color(255, 255, 255, sf::Uint8(Utils::Lerp(0,255, timer / 0.5f))));
	logo->sprite.setScale(1.8f, timer / 0.5f * 1.8f);

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Up)|| INPUT_MGR.GetKeyDown(sf::Keyboard::Down))
	{
		se_Sound.play();
		switch (select)
		{
		case 0:
			select = 1;
			startButton->sprite.setTextureRect(buttonActive[0]);
			exitButton->sprite.setTextureRect((buttonActive[3]));
			break;
		case 1:
			select = 0;
			startButton->sprite.setTextureRect(buttonActive[1]);
			exitButton->sprite.setTextureRect((buttonActive[2]));
			break;
		}
	}
	else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		se_pickSound.play();
		switch (select)
		{
		case 0:
			backGround->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/TitleBackground.png"));
			for (auto go : gameObjects)
			{
				go->SetActive(false);
			}
			backGround->SetActive(true);
			loading_kor->SetActive(true);
			loading_Eng->SetActive(true);

			change = true;
			break;
		case 1:
			window.close();
			break;
		}
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
