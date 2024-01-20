#pragma once
#include "CComponent.h"
// =======================================
// CCollider2D: �浹ü�� ����, �����ϴ� Components
// =======================================
// - ��ü�� �浹�� �� �ְ� ��(�浹ü�� ����)

enum class COLLIDER2D_TYPE
{
    RECT,
    CIRCLE,
};

class CCollider2D :
    public CComponent
{
    COLLIDER2D_TYPE m_Type;
    Vec3            m_vOffsetPos;
    Vec3            m_vOffsetScale;
    Matrix          m_matColWorld;
    bool            m_bAbsolute;    // Owner�� Scale ���� ������ ����
    int             m_CollisionCount;

public:
    virtual void finaltick() override;
    void BeginOverlap(CCollider2D* _OtherCollider);
    void Overlap(CCollider2D* _OtherCollider);
    void EndOverlap(CCollider2D* _OtherCollider);

public:
    void SetColliderType(COLLIDER2D_TYPE _Type) { m_Type = _Type; }
    void SetOffsetPos(Vec2 _vOffset) { m_vOffsetPos = Vec3(_vOffset.x, _vOffset.y, 0.f); }
    void SetOffsetScale(Vec2 _vOffsetScale) { m_vOffsetScale = Vec3(_vOffsetScale.x, _vOffsetScale.y, 1.f); }
    void SetAbsolute(bool _bAbsol) { m_bAbsolute = _bAbsol; }
    COLLIDER2D_TYPE GetColliderType() { return m_Type; }
    Vec2 GetOffsetPos() { return Vec2(m_vOffsetPos.x, m_vOffsetPos.y); }
    Vec2 GetOffsetScale() { return Vec2(m_vOffsetScale.x, m_vOffsetScale.y); }
    const Matrix& GetColliderWorldMat() { return m_matColWorld; }
    bool IsAbsolute() { return m_bAbsolute; }

public:
    CCollider2D();
    ~CCollider2D();
};

