#pragma once
#include "singleton.h"
class CLevel;

class CLevelMgr :
	public CSingleton<CLevelMgr>
{
	SINGLETON(CLevelMgr);

private:
	CLevel* m_CurLevel;

public:
	CLevel* GetCurrentLevel()
	{
		return m_CurLevel;
	}

public:
	void init();
	void tick();
};

