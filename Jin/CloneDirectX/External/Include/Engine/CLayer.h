#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*> m_vecParent;

    vector<CGameObject*> m_vecObjects;

    int  m_iLayerIdx;

private:
    void begin();
    void tick();
    void finaltick();
    void render();

public:
    void DetachGameObject(CGameObject* _Object);
    void RegisterGameObject(CGameObject* _Object) { m_vecObjects.push_back(_Object); }


public:
    CLayer();
    ~CLayer();


private:
    void AddObject(CGameObject* _Object, bool _bMove);
    friend class CLevel;
};

