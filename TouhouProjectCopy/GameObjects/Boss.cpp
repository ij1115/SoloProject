#include "stdafx.h"
#include "Boss.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"
#include "scene.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Bullet.h"


void Boss::Init()
{
	SpriteGo::Init();

	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossIdle.csv"));
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossRightMove.csv"));
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossLeftMove.csv"));
	bossAnimation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/BossAction.csv"));

	bossAnimation.SetTarget(&sprite);

	SetOrigin(Origins::MC);
}

void Boss::Reset()
{
	SpriteGo::Reset();

	hit.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/se_damage00.wav"));
	hit.setVolume(25);
	attack.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/se_tan02.wav"));
	attack.setVolume(15);
	SetPosition(gameView.left + gameView.width / 2, gameView.top -100.f);
	bossAnimation.Play("BossIdle");
	SetOrigin(origin);
	SetActive(true);
	action = false;
	speed = 0.0f;
	timer = 0.f;
	dir = { 0.f,0.f };
	count = 0;
	ResetHP();
	phaseEffect->SetActive(false);
	phase = false;
}

void Boss::Release()
{
	SpriteGo::Release();

	SCENE_MGR.GetCurrScene()->RemoveGo(this->hitbox);
	pool->Return(this->hitbox);
}

void Boss::Update(float dt)
{
	SpriteGo::Update(dt);
	bossAnimation.Update(dt);

	if (player->GetPlaying() && !player->GetChangePhase())
	{
		pDelay -= dt;

		FollowPos();
		//std::cout << delayTime << std::endl;
		//std::cout << hp << std::endl;
		if (phaseEffect->GetActive())
		{
			phaseEffect->sprite.rotate(360 * dt);
		}

		if (!action)
		{
			if (!phase)
			{
				actionNum = Utils::RandomRange(1, 8);
				action = true;
			}
			else if (phase)
			{
				actionNum = Utils::RandomRange(1, 11);
				action = true;
			}
		}
		else if (action)
		{
			switch (actionNum)
			{
			case 1:
				MovePatten1();
				break;
			case 2:
				MovePatten2();
				break;
			case 3:
				MovePatten3();
				break;
			case 4:
				MovePatten4();
				break;
			case 5:
				MovePatten5();
				break;
			case 6:
				MovePatten6();
				break;
			case 7:
				MovePatten7();
				break;
			case 8:
				MovePatten8();
				break;
			case 9:
				MovePatten9();
				break;
			case 10:
				MovePatten10();
				break;
			}
		}

	}
	if (delay)
	{
		delayTime -= dt;
	}
	if (!move)
	{
		dir = { 0.f,0.f };
	}

	timer += dt * speed;

	if (timer > 1.f)
	{
		timer = 1.f;
	}

	Move();


	if (curve && !strike)
	{
		position = BezierMove(startMovePos, middleMovePos, endMovePos, timer);
	}
	else if (!curve && strike)
	{
		position += dir * speed * dt;
	}

	SetPosition(position);

}

void Boss::SetHitBoxPool(ObjectPool<HitboxGo>* hitBoxPool)
{
	this->pool = hitBoxPool;
}

void Boss::SetTargetPos()
{
	targetPos = player->GetPosition();
}

void Boss::SetPlayer(Player* player)
{
	this->player = player;
}

void Boss::Fire()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (sceneGame != nullptr)
	{
		for (int i = 0; i < 20; ++i)
		{
			sceneGame->GetBullet(bullet);
			bullet->SetUser((Bullet::User)1);
			bullet->SetBulletType((Bullet::Types)0);
			bullet->Init();
			bullet->Reset();
			bullet->BulletStatPos({ position.x,position.y - 25.f });
			bullet->SetCount();
			bullet->SetSpeed(0.f);
			bullet->SetFire(1);
			sceneGame->AddGo(bullet);
		}
	}
}
void Boss::Fire2()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (sceneGame != nullptr)
	{
		for (int i = 0; i < 45; ++i)
		{
			sceneGame->GetBullet(bullet);
			bullet->SetUser((Bullet::User)1);
			bullet->SetBulletType((Bullet::Types)0);
			bullet->Init();
			bullet->Reset();
			bullet->BulletStatPos({ position.x,position.y - 25.f });
			bullet->SetCount();
			bullet->SetSpeed(0.f);
			bullet->SetDir({ 1.f, 1.f});
			bullet->BulletRotate(8* i);
			bullet->SetFire(2);
			sceneGame->AddGo(bullet);
		}
	}
}
void Boss::Fire3()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (sceneGame != nullptr)
	{
		sceneGame->GetBullet(bullet);
		bullet->SetUser((Bullet::User)1);
		bullet->SetBulletType((Bullet::Types)0);
		bullet->Init();
		bullet->Reset();
		bullet->BulletStatPos({ position.x,position.y - 25.f });
		bullet->SetCount();
		bullet->SetSpeed(0.f);
		bullet->SetFire(3);
		sceneGame->AddGo(bullet);
	}
}
void Boss::Fire4(int c)
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (sceneGame != nullptr)
	{
		sceneGame->GetBullet(bullet);
		bullet->SetUser((Bullet::User)1);
		bullet->SetBulletType((Bullet::Types)0);
		bullet->Init();
		bullet->Reset();
		bullet->SetCount();
		bullet->SetPosition(position.x + 25.f, position.y);
		bullet->SetDir({ 1.f, 0.f });
		bullet->SetDelayTime(0.01f * c);
		bullet->SetSpeed(0.f);
		bullet->SetFire(4);
		sceneGame->AddGo(bullet);

		sceneGame->GetBullet(bullet);
		bullet->SetUser((Bullet::User)1);
		bullet->SetBulletType((Bullet::Types)0);
		bullet->Init();
		bullet->Reset();
		bullet->SetCount();
		bullet->SetPosition(position.x - 25.f, position.y);
		bullet->SetDir({ -1.f, 0.f });
		bullet->SetDelayTime(0.01f * c);
		bullet->SetSpeed(0.f);
		bullet->SetFire(4);
		sceneGame->AddGo(bullet);

		sceneGame->GetBullet(bullet);
		bullet->SetUser((Bullet::User)1);
		bullet->SetBulletType((Bullet::Types)0);
		bullet->Init();
		bullet->Reset();
		bullet->SetCount();
		bullet->SetPosition(position.x, position.y+25.f);
		bullet->SetDir({ 0.f, 1.f });
		bullet->SetDelayTime(0.01f * c);
		bullet->SetSpeed(0.f);
		bullet->SetFire(4);
		sceneGame->AddGo(bullet);

		sceneGame->GetBullet(bullet);
		bullet->SetUser((Bullet::User)1);
		bullet->SetBulletType((Bullet::Types)0);
		bullet->Init();
		bullet->Reset();
		bullet->SetCount();
		bullet->SetPosition(position.x, position.y-25.f);
		bullet->SetDir({ 0.f, -1.f });
		bullet->SetDelayTime(0.01f * c);
		bullet->SetSpeed(0.f);
		bullet->SetFire(4);
		sceneGame->AddGo(bullet);
	}
}
void Boss::Fire5(int c)
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (sceneGame != nullptr)
	{
		for (int i = 0; i <5; ++i)
		{
			sceneGame->GetBullet(bullet);
			bullet->SetUser((Bullet::User)1);
			bullet->SetBulletType((Bullet::Types)0);
			bullet->Init();
			bullet->Reset();
			bullet->SetCount();
			bullet->SetPosition(position.x, position.y+25.f);
			bullet->SetDir({ 0.f, 1.f });
			bullet->SetDelayTime(0.01f* c);
			bullet->SetSpeed(0.f);
			bullet->BulletRotate(-15 * i);
			bullet->SetFire(5);
			sceneGame->AddGo(bullet);
		}

		for (int i = 0; i < 5; ++i)
		{
			sceneGame->GetBullet(bullet);
			bullet->SetUser((Bullet::User)1);
			bullet->SetBulletType((Bullet::Types)0);
			bullet->Init();
			bullet->Reset();
			bullet->SetCount();
			bullet->SetPosition(position.x, position.y-25.f);
			bullet->SetDir({ 0.f, -1.f });
			bullet->SetDelayTime(0.01f * c);
			bullet->SetSpeed(0.f);
			bullet->BulletRotate(15 * i);
			bullet->SetFire(5);
			sceneGame->AddGo(bullet);
		}
	}
}
void Boss::Fire6(int c)
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (sceneGame != nullptr)
	{
		for (int i = 0; i < 5; ++i)
		{
			sceneGame->GetBullet(bullet);
			bullet->SetUser((Bullet::User)1);
			bullet->SetBulletType((Bullet::Types)0);
			bullet->Init();
			bullet->Reset();
			bullet->SetCount();
			bullet->SetPosition(position.x, position.y + 25.f);
			bullet->SetDir({ 0.f, 1.f });
			bullet->SetDelayTime(0.01f * c);
			bullet->SetSpeed(0.f);
			bullet->BulletRotate(15 * i);
			bullet->SetFire(5);
			sceneGame->AddGo(bullet);
		}

		for (int i = 0; i < 5; ++i)
		{
			sceneGame->GetBullet(bullet);
			bullet->SetUser((Bullet::User)1);
			bullet->SetBulletType((Bullet::Types)0);
			bullet->Init();
			bullet->Reset();
			bullet->SetCount();
			bullet->SetPosition(position.x, position.y - 25.f);
			bullet->SetDir({ 0.f, -1.f });
			bullet->SetDelayTime(0.01f * c);
			bullet->SetSpeed(0.f);
			bullet->BulletRotate(-15 * i);
			bullet->SetFire(5);
			sceneGame->AddGo(bullet);
		}
	}
}
void Boss::Fire7()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (sceneGame != nullptr)
	{
		for (int i = 0; i < 16; ++i)
		{
			sceneGame->GetBullet(bullet);
			bullet->SetUser((Bullet::User)1);
			bullet->SetBulletType((Bullet::Types)1);
			bullet->Init();
			bullet->Reset();
			bullet->BulletStatPos({ position.x,position.y - 25.f });
			bullet->SetCount();
			bullet->SetSpeed(0.f);
			bullet->SetDir({ 1.f, 1.f });
			bullet->BulletRotate(22.5f * i);
			bullet->SetFire(5);
			sceneGame->AddGo(bullet);
		}
	}
}
void Boss::Fire8()
{
	Scene* scene = SCENE_MGR.GetCurrScene();
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
	if (sceneGame != nullptr)
	{
		for (int i = 0; i < 16; ++i)
		{
			sceneGame->GetBullet(bullet);
			bullet->SetUser((Bullet::User)1);
			bullet->SetBulletType((Bullet::Types)1);
			bullet->Init();
			bullet->Reset();
			bullet->BulletStatPos({ position.x,position.y - 25.f });
			bullet->SetCount();
			bullet->SetSpeed(0.f);
			bullet->SetDir({ 1.f, 1.f });
			bullet->BulletRotate(33.75f * i);
			bullet->SetFire(5);
			sceneGame->AddGo(bullet);
		}
	}
}

void Boss::Move()
{
	if (bossAnimation.GetCurrIds() != "BossLeftMove")
	{
		if (dir.x < 0)
		{
			bossAnimation.Play("BossLeftMove");
		}
	}
	if (bossAnimation.GetCurrIds() != "BossRightMove")
	{
		if (dir.x > 0)
		{
			bossAnimation.Play("BossRightMove");
		}
	}
	if (bossAnimation.GetCurrIds() != "BossIdle")
	{
		if (dir.x == 0&&!bossPrivatePose)
		{
			bossAnimation.Play("BossIdle");
		}
	}
	if (bossAnimation.GetCurrIds() != "BossAction")
	{
		if (dir.x == 0 && bossPrivatePose)
		{
			bossAnimation.Play("BossAction");
		}
	}
}

sf::Vector2f Boss::BezierMove(const sf::Vector2f& pos0, const sf::Vector2f& pos1, const sf::Vector2f& pos2, float moveT)
{
	float u = 1.f - moveT;
	float tt = moveT * moveT;
	float uu = u * u;

	sf::Vector2f p = uu * pos0;
	p += 2.f * u * moveT * pos1;
	p += tt * pos2;

	return p;
}


// 1 Phase
void Boss::MovePatten1() // 좌상단에서 우상단 곡선 이동 하면서 탁막 발사
{
	switch (count)
	{
	case 0:
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x - 200.f);
		SetEndMovePosY(center.y - 200.f);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		break;
	case 1:
		move = true;
		SetMiddleMovePosX(center.x);
		SetMiddleMovePosY(center.y);
		SetEndMovePosX(center.x + 300.f);
		SetEndMovePosY(center.y - 250.f);
		SetDirX(1.f);
		SetSpeed(0.5f);
		SetCurve();
		CheckEndPosTypeCurve();
		pMaxCount = 20;
		pCount = 0;
		pDelay = 0.01f;
		break;
	case 2:
		move = true;
		SetEndMovePosX(center.x);
		SetEndMovePosY(center.y);
		SetSpeed(400.f);
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire();
			attack.play();
			pCount++;
			pDelay = 0.1f;
		}
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		break;
	case 3:
		move = true;
		SetMiddleMovePosX(center.x - 100.f);
		SetMiddleMovePosY(center.y - 200.f);
		SetEndMovePosX(center.x - 250.f);
		SetEndMovePosY(center.y - 50.f);
		SetDirX(-1.f);
		SetSpeed(0.5f);
		SetCurve();
		CheckEndPosTypeCurve();
		break;
	case 4:
		SetdelayTime(1.5f);
		TimeOut();
		break;
	case 5:
		PoseFalse();
		action = false;
		count = 0;
	}
}
void Boss::MovePatten2() // 우상단에서 좌상단 곡선 이동 하면서 탁막 발사
{
	switch (count)
	{
	case 0:
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x + 200.f);
		SetEndMovePosY(center.y - 200.f);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		break;
	case 1:
		move = true;
		SetMiddleMovePosX(center.x);
		SetMiddleMovePosY(center.y);
		SetEndMovePosX(center.x - 300.f);
		SetEndMovePosY(center.y - 250.f);
		SetDirX(-1.f);
		SetSpeed(0.5f);
		SetCurve();
		CheckEndPosTypeCurve();
		pMaxCount = 20;
		pCount = 0;
		pDelay = 0.01f;
		break;
	case 2:
		move = true;
		SetEndMovePosX(center.x);
		SetEndMovePosY(center.y);
		SetSpeed(400.f);
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire();
			attack.play();
			pCount++;
			pDelay = 0.1f;
		}
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		break;

	case 3:
		move = true;
		SetMiddleMovePosX(center.x - 100.f);
		SetMiddleMovePosY(center.y - 200.f);
		SetEndMovePosX(center.x + 250.f);
		SetEndMovePosY(center.y - 50.f);
		SetDirX(1.f);
		SetSpeed(0.5f);
		SetCurve();
		CheckEndPosTypeCurve();
		break;
	case 4:
		SetdelayTime(1.5f);
		TimeOut();
		break;
	case 5:
		PoseFalse();
		action = false;
		count = 0;
		break;
	}
}
void Boss::MovePatten3() // 중앙에서 원형으로 발사
{
	switch (count)
	{
	case 0:
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x);
		SetEndMovePosY(center.y-200.f);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		pMaxCount = 15;
		pCount = 0;
		pDelay = 0.001f;
		break;
	case 1:
		PoseTrue();
		SetdelayTime(1.5f);
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire2();
			attack.play();
			pCount++;
			pDelay = 0.05f;
		}
		TimeOut();
		break;
	case 2:
		PoseFalse();
		SetdelayTime(3.f);
		TimeOut();
		break;
	case 3:
		action = false;
		count = 0;
		break;
	}
}
void Boss::MovePatten4() // 상단 중간 좌 우 이동
{
	switch (count)
	{
	case 0:
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x+200);
		SetEndMovePosY(center.y - 200.f);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		pMaxCount = 10;
		pCount = 0;
		pDelay = 0.001f;
		break;

	case 1:
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire3();
			attack.play();
			pCount++;
			pDelay = 0.01f;
		}
		else if(pMaxCount<=pCount)
		{
			CountUp();
		}
		break;
	case 2:
		move = true;
		SetEndMovePosX(center.x);
		SetEndMovePosY(center.y - 200.f);
		SetSpeed(700.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		pMaxCount = 10;
		pCount = 0;
		pDelay = 0.001f;
		break;
	case 3:
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire3();
			attack.play();
			pCount++;
			pDelay = 0.01f;
		}
		else if (pMaxCount <= pCount)
		{
			CountUp();
		}
		break;
	case 4:
		move = true;
		SetEndMovePosX(center.x - 200.f);
		SetEndMovePosY(center.y - 200.f);
		SetSpeed(700.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		pMaxCount = 10;
		pCount = 0;
		pDelay = 0.001f;
		break;
	case 5:
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire3();
			attack.play();
			pCount++;
			pDelay = 0.01f;
		}
		else if (pMaxCount <= pCount)
		{
			CountUp();
		}
		break;
	case 6:
		action = false;
		count = 0;
		break;
	}
}
void Boss::MovePatten5() // 센터에서 사각형 패턴
{
	switch (count)
	{
	case 0:
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x);
		SetEndMovePosY(center.y);
		SetSpeed(500.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		pMaxCount = 20;
		pCount = 0;
		pDelay = 0.01f;
		break;

	case 1:
		PoseTrue();
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire4(pCount);
			attack.play();
			pCount++;
			pDelay = 0.05f;
		}
		else if (pMaxCount <= pCount)
		{
			CountUp();
		}
		break;

	case 2:
		SetdelayTime(0.1f);
		pMaxCount = 20;
		pCount = 0;
		pDelay = 0.01f;
		TimeOut();
		break;

	case 3:
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire4(pCount);
			attack.play();
			pCount++;
			pDelay = 0.05f;
		}
		else if (pMaxCount <= pCount)
		{
			CountUp();
		}
		break;

	case 4:
		SetdelayTime(0.1f);
		pMaxCount = 20;
		pCount = 0;
		pDelay = 0.01f;
		TimeOut();
		break;

	case 5:
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire4(pCount);
			attack.play();
			pCount++;
			pDelay = 0.05f;
		}
		else if (pMaxCount <= pCount)
		{
			CountUp();
		}
		break;

	case 6:
		SetdelayTime(0.1f);
		pMaxCount = 20;
		pCount = 0;
		pDelay = 0.01f;
		TimeOut();
		break;

	case 7:
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire4(pCount);
			attack.play();
			pCount++;
			pDelay = 0.05f;
		}
		else if (pMaxCount <= pCount)
		{
			CountUp();
		}
		break;

	case 8:
		SetdelayTime(1.f);
		TimeOut();
		break;

	case 9:
		PoseFalse();
		action = false;
		count = 0;
		break;
	}
}
void Boss::MovePatten6()
{
	switch (count)
	{
	case 0:
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x + 200.f);
		SetEndMovePosY(center.y - 200.f);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		pMaxCount = 20;
		pCount = 0;
		pDelay = 0.01f;
		break;
	case 1:
		move = true;
		SetMiddleMovePosX(center.x);
		SetMiddleMovePosY(center.y);
		SetEndMovePosX(center.x - 300.f);
		SetEndMovePosY(center.y - 250.f);
		SetDirX(-1.f);
		SetSpeed(0.5f);
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire5(pCount);
			attack.play();
			pCount++;
			pDelay = 0.2f;
		}
		SetCurve();
		CheckEndPosTypeCurve();
		break;
	case 2:
		action = false;
		count = 0;
		break;
	}
}
void Boss::MovePatten7()
{
	switch (count)
	{
	case 0:
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x - 200.f);
		SetEndMovePosY(center.y - 200.f);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		pMaxCount = 20;
		pCount = 0;
		pDelay = 0.01f;
		break;
	case 1:
		move = true;
		SetMiddleMovePosX(center.x);
		SetMiddleMovePosY(center.y);
		SetEndMovePosX(center.x + 300.f);
		SetEndMovePosY(center.y - 250.f);
		SetDirX(1.f);
		SetSpeed(0.5f);
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire6(pCount);
			attack.play();
			pCount++;
			pDelay = 0.2f;
		}
		SetCurve();
		CheckEndPosTypeCurve();
		break;
	case 2:
		action = false;
		count = 0;
		break;
	}
}
void Boss::MovePatten8()
{
	switch (count)
	{
	case 0:
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x - 200.f);
		SetEndMovePosY(center.y - 200.f);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		pMaxCount = 15;
		pCount = 0;
		pDelay = 0.001f;
		break;
	case 1:
		PoseTrue();
		SetdelayTime(1.5f);
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire2();
			attack.play();
			pCount++;
			pDelay = 0.05f;
		}
		TimeOut();
		break;
	case 2:
		PoseFalse();
		SetdelayTime(1.f);
		TimeOut();
		break;
	case 3:
		action = false;
		count = 0;
		break;
	}
}
void Boss::MovePatten9()
{
	switch (count)
	{
	case 0:
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x + 200.f);
		SetEndMovePosY(center.y - 200.f);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		pMaxCount = 15;
		pCount = 0;
		pDelay = 0.001f;
		break;
	case 1:
		PoseTrue();
		SetdelayTime(1.5f);
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			Fire2();
			attack.play();
			pCount++;
			pDelay = 0.05f;
		}
		TimeOut();
		break;
	case 2:
		PoseFalse();
		SetdelayTime(1.f);
		TimeOut();
		break;
	case 3:
		action = false;
		count = 0;
		break;
	}
}
void Boss::MovePatten10()
{
	switch (count)
	{
	case 0:
		move = true;
		PattenSetPos();
		SetEndMovePosX(center.x);
		SetEndMovePosY(center.y);
		SetSpeed(300.f);
		SetStrike();
		SetStrikeDir();
		CheckEndPosTypeStrike();
		pMaxCount = 15;
		pCount = 0;
		pDelay = 0.25f;
		break;
	case 1:
		PoseTrue();
		SetdelayTime(1.5f);
		if (pCount < pMaxCount && pDelay < 0.f)
		{
			if ((pCount % 2) == 0)
			{
				Fire7();
			}
			else if((pCount %2)!=0)
			{
				Fire8();
			}
			attack.play();
			pCount++;
			pDelay = 0.25f;
		}
		else if (pCount >= pMaxCount)
		{
			CountUp();
		}
		break;
	case 2:
		PoseFalse();
		SetdelayTime(1.f);
		TimeOut();
		break;
	case 3:
		action = false;
		count = 0;
		break;
	}
}

void Boss::CheckEndPosTypeCurve()
{
	if (position == endMovePos && move)
	{
		move = false;
		speed = 0.f;
		startMovePos = endMovePos;
		pattenActive = false;
		count++;
		timer = 0;
	}
}
void Boss::CheckEndPosTypeStrike()
{
	length = Utils::Distance(position, endMovePos);
	if (length <= 10.f)
	{
		move = false;
		speed = 0.f;
		position = endMovePos;
		startMovePos = endMovePos;
		pattenActive = false;
		count++;
		timer = 0;
	}
}
void Boss::SetStrikeDir()
{
	dir = Utils::Normalize(endMovePos-startMovePos);
}
void Boss::PattenSetPos()
{
	SetStartMovePosX(position.x);
	SetStartMovePosY(position.y);
}
void Boss::SetdelayTime(float t)
{
	if (!delay)
	{
		delay = true;
		delayTime = t;
	}
}
float Boss::GetHitBox()
{
	return this->hitbox->GetRaidus();
}

//gameViewSize.width = 914.5f;
//gameViewSize.height = 640.f;
