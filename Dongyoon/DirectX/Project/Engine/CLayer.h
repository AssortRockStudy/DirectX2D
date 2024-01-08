#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*>    m_vecParent;
    vector<CGameObject*>    m_vecObjects;

    int                     m_iLayerIdx;

public:
    void begin();
    void tick();
    void finaltick();
    void render();
    
public:
    //특정 obj를 layer에서 제거
    void DetachGameObject(CGameObject* _Object);

    void RegisterGameObject(CGameObject* _Object) { m_vecObjects.push_back(_Object); }

private:
    void AddObject(CGameObject* _Object, bool _bMove);
  
public:
    CLayer();
    ~CLayer();

    friend class CLevel;
};

