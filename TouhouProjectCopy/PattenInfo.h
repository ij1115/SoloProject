#pragma once

enum class User
{
	Player,
	Enemy,
	NONE,
};
enum class BulletInfoType
{
	Speed,
	Direction,
	Rotate,
	Delay,
};

struct Patten
{
	std::string textureId;
	BulletInfoType type;
	float value;
};

struct PattenInfo
{
	User user;
	std::vector<Patten> bulletAction;

	bool LoadFromFile(const std::string path);
};