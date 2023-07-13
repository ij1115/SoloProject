#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
void Player::Init()
{

}

void Player::Reset()
{

}

void Player::Update(float dt)
{
	animation.Update(dt);
	SpriteGo::Update(dt);

}
