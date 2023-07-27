#pragma once
#include "stdafx.h"

enum class AnimationLoopTypes
{
	Single,
	Loop,
};
struct AnimationFrame
{
	std::string textureId;
	sf::IntRect tecCoord;
	//std::function<void()> action;
};

struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;
	AnimationLoopTypes loopType;

	int fps; // 초당 프레임

	bool LoadFromFile(const std::string path);
};