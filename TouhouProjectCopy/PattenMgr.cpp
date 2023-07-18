#include "stdafx.h"
#include "PattenMgr.h"
#include "rapidcsv.h"

PattenMgr::~PattenMgr()
{
	for (auto pair : patten)
	{
		delete pair.second;
	}
	patten.clear();
}


void PattenMgr::Init()
{
	LoadFromFile("scripts/BulletList.csv");
}

void PattenMgr::LoadFromFile(const std::string path)
{
	rapidcsv::Document doc(path);
	pattenId = doc.GetCell<std::string>(0, 0);
	
	for (int i = 3; i < doc.GetRowCount(); ++i)
	{
		auto rows = doc.GetRow<std::string>(i);
		Load(rows[0]);
	}
}

void PattenMgr::Load(const std::string path)
{
	auto it = patten.find(path);
	if (patten.end() == it)
	{
		auto pattenInfo = new PattenInfo();
		pattenInfo->LoadFromFile(path);
		patten.insert({ path, pattenInfo });
	}
}