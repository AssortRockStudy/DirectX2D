#pragma once
#include "singleton.h"
class CGC :
    public CSingleton<CGC>
{
    SINGLETON(CGC);

private:
    vector<class CEntity*> m_vecEntity;

public:
    void tick();

    void Add(CEntity* _Entity) { m_vecEntity.push_back(_Entity); }
};

