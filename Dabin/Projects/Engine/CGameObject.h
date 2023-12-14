#pragma once
#include "CEntity.h"

// =======================================
// CGameObject: 모든 GameObject가 상속하는 parent class
// =======================================
class CComponent;
class CGameObject :
    public CEntity
{
private:
    CComponent* m_arrCom[(UINT)COMPONENT_TYPE::END];    // 배열로 관리

public:
    CGameObject();
    ~CGameObject();
};

