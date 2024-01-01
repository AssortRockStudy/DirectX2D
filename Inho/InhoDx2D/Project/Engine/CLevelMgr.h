#pragma once
#include "singleton.h"
class CLevelMgr :
    public CSingleton<CLevelMgr>
{
    SINGLE(CLevelMgr)

private:
    class CLevel* m_CurLevel;

public:
    void init();

    void tick();
    void render();

public:
    CLevel* GetCurrentLevel() { return m_CurLevel; }
};

