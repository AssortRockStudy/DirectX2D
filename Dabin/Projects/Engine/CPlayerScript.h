#pragma once
#include "CScript.h"

// =======================================
// CPlayerScript: Player ������
// =======================================
// imp01. player controller

class CPlayerScript :
    public CScript
{
private:
    float   m_Speed;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CPlayerScript();
    ~CPlayerScript();
};

