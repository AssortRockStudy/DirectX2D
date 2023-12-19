#pragma once
#include "CEntity.h"

// =======================================
// CLevel: GameObject가 배치되는 Scene
// =======================================
class CLayer;
class CGameObject;

class CLevel :
    public CEntity
{
private:
    CLayer* m_arrLayer[LAYER_MAX];

public:
    void begin();
    void tick();
    void finaltick();
    void render();

public:
    void AddObject(CGameObject* _Object, int _LayerIdx);

public:
    CLevel();
    ~CLevel();
};

