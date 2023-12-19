#pragma once
#include "CComponent.h"

// =======================================
// CTransform: Object 이동 기능 구현, 관리
// =======================================
// - 이동: constant buffer로 transform 값 옮거야 함

class CTransform :
    public CComponent
{
private:
    Vec3    m_vRelativePos;
    Vec3    m_vRelativeScale;
    Vec3    m_vRelativeRotation;
    Vec3    m_arrDir[3]; // Right, Up, Front (부호바꾸면 되므로 세 값만 알면 6방향의 값 알 수 있음)
    Matrix  m_matWorld;

public:
    virtual void finaltick() override;
    virtual void UpdateData() override;

public:    
    void SetRelativePos(Vec3 _Pos) { m_vRelativePos = _Pos; }
    void SetRelativeScale(Vec3 _Scale) { m_vRelativeScale = _Scale; }
    void SetRelativeRotation(Vec3 _Rotation) { m_vRelativeRotation = _Rotation; }
    Vec3 GetRelativePos() { return m_vRelativePos; }
    Vec3 GetRelativeScale() { return m_vRelativeScale; }
    Vec3 GetRelativeRotation() { return m_vRelativeRotation; }
    const Matrix& GetWorldMat() { return m_matWorld; }

public:
    CTransform();
    ~CTransform();
};