#pragma once
#include "CEntity.h"
class CGameObject :
    public CEntity
{
private:
    class CComponent* m_arrCom[(UINT)COMPONENT_TYPE::END];

public:
    CGameObject();
    ~CGameObject();
};

