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
    vector<CGameObject*>    m_vecObjects;
    int                     m_iLayerIdx;

private:
    void begin();
    void tick();
    void finaltick();

private:
    void AddObject(CGameObject* _Object, bool _bMove = false);

public:
    void RegisterGameObject(CGameObject* _Object) { m_vecObjects.push_back(_Object); }
    void DetachGameObject(CGameObject* _Object);
    const vector<CGameObject*>& GetLayerObjects() { return m_vecObjects; }
    const vector<CGameObject*>& GetParentObjects() { return m_vecParent; }
    int GetLayerIdx() { return m_iLayerIdx; }

public:
    CLayer();
    ~CLayer();

    friend class CLevel;
};

