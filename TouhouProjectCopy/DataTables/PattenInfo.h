#pragma once

enum class BulletInfoType
{
	PositionX,
	PositionY,
	Speed,
	Direction,
	Rotate,
	Delay,
	Delete,
};

struct Patten
{
	BulletInfoType type;
	float value;
};

struct PattenInfo
{
	std::string id;
	std::vector<Patten> bulletAction;

	bool LoadFromFile(const std::string path);
};