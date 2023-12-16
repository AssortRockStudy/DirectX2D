#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*>    m_vecParent;

public:
    void begin();
    void tick();
    void finaltick();
    void render();

private:
    void AddObject(CGameObject* _Object) { m_vecParent.push_back(_Object); }

public:
    CLayer();
    ~CLayer();

    friend class CLevel;
};

