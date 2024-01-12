#pragma once
#include "singleton.h"

// =======================================
// CLevelMgr: Level ����, ����
// =======================================

class CLevel;

class CLevelMgr :
    public CSingleton<CLevelMgr>
{
    SINGLE(CLevelMgr)

private:
    CLevel* m_CurLevel;

public:
    void init();
    void tick();

public:
    CLevel* GetCurrentLevel() { return m_CurLevel; }
};

