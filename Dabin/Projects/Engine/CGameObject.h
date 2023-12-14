#pragma once
#include "CEntity.h"

// =======================================
// CGameObject: ��� GameObject�� ����ϴ� parent class
// =======================================
class CComponent;
class CGameObject :
    public CEntity
{
private:
    CComponent* m_arrCom[(UINT)COMPONENT_TYPE::END];    // �迭�� ����

public:
    CGameObject();
    ~CGameObject();
};

