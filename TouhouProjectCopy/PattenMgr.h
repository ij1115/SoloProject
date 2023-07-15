#pragma once
#include "Singleton.h"

class PattenMgr : public Singleton<PattenMgr>
{
	friend Singleton<PattenMgr>;

protected:
	
	PattenMgr() = default;
	virtual ~PattenMgr() override;

	std::unordered_map<PattenInfo> patten;

public:
	void Init();

};

#define PATTEN_MGR (PattenMgr::Instance())