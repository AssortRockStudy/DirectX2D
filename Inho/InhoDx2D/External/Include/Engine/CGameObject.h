#pragma once
#include "CEntity.h"
class CGameObject :
    public CEntity
{
private:
    class CComponent* m_arrCom[(UINT)COMPONENT_TYPE::END];

public:
    void begin();
    void tick();
    void finaltick();
    void render();

public:
    void AddComponent(CComponent* _Component);
public:
    CGameObject();
    ~CGameObject();
};

