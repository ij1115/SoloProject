#include "stdafx.h"
#include "rapidcsv.h"

bool PattenInfo::LoadFromFile(const std::string path)
{
	rapidcsv::Document doc(path);
	

	return true;
}
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