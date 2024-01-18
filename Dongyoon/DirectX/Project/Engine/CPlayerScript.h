#pragma once
#include "CScript.h"
class CPlayerScript :
    public CScript
{
private:
    float m_Speed;

public:
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherColldier);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CPlayerScript();
    ~CPlayerScript();
};

