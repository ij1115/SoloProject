#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"
#include "ShapeGo.h"

class Player : public SpriteGo
{
public:
	struct ClipInfo
	{
		std::string idle;
		std::string move;
		bool flipX = false;
		sf::Vector2f point;
	};
protected:
	AnimationController animation;

	std::vector<ClipInfo> clipInfos;
	ClipInfo currentClipInfo;
	
public:
	Player(const std::string& textureId= "", const std::string& n= "")
		: SpriteGo(textureId,n) {}
	virtual ~Player() override { Release(); };

	virtual void Init() override;
	virtual void Reset() override;
	
	virtual void Update(float dt) override;

};

