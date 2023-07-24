#pragma once
#include "Singleton.h"

class PattenMgr : public Singleton<PattenMgr>
{
	friend Singleton<PattenMgr>;

protected:
	
	PattenMgr() = default;
	virtual ~PattenMgr() override;

	std::unordered_map<std::string, PattenInfo*> patten;
	std::string pattenId;
	PattenInfo* pattenInfo = nullptr;

	sf::Sprite* target = nullptr;

public:
	void Init();
	void LoadFromFile(const std::string path);
	void Load(const std::string path);
};

#define PATTEN_MGR (PattenMgr::Instance())