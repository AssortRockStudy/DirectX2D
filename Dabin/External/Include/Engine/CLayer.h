#pragma once
#include "CEntity.h"

// =======================================
// Layer: Level에 올라가는 Object의 계층
// =======================================

class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*>    m_vecParent;

private:
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

