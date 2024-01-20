#pragma once
#include "CComponent.h"

// =======================================
// CScript: ��� scprit��  parent class
// =======================================
// - ������ ���� �����δ� Scripts class�� ����� scripts�� �ۼ��� ����

class CScript :
    public CComponent
{
private:
    UINT    m_iScriptType;

public:
    virtual void finaltick() final {}
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {};
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {};
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {};

public:
    CScript();
    ~CScript();
};