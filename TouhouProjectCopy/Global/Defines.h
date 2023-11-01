#pragma once

#define _USE_MATH_DEFINES

enum class Languages
{
	KOR,
	ENG,
	JP,
	COUNT,
};

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
	AnimationClip,
};

enum class SceneId
{
	None = -1,
	Title,
	Game,
	Count,
};

enum class UpdateState
{
	None,
	Event,
	Boss,
	Play,
	Ending,
	Pause,
	Dead,
};

#include "AniamtionClip.h"
#include "PattenInfo.h"