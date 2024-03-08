#pragma once

#include "CComponent.h"


class CTransform :
    public CComponent
{
private:
    Vec3        m_vRelativePos;             // 위치
    Vec3        m_vRelativeScale;           // 크기
    Vec3        m_vRelativeRotation;        // 회전량
    Vec3        m_arrLocalDir[3];           // 물체의 현재 방향   Ringt, Up, Front(로컬)
    Vec3        m_arrWorldDir[3];           // Right, Up, Front(월드)


    Matrix      m_matWorld;          // 물체의 상태 행렬(변환 이동행렬)
    bool        m_bAbsolute;

public:
    virtual void finaltick() override;
    virtual void UpdateData() override;

public:
    void SetRelativePos(Vec3 _Pos) { m_vRelativePos = _Pos; }
    void SetRelativeScale(Vec3 _Scale) { m_vRelativeScale = _Scale; }
    void SetRelativeRotation(Vec3 _Rotation) { m_vRelativeRotation = _Rotation; }

    void SetWorldMat(const Matrix _matWorld) { m_matWorld = _matWorld; }

    Vec3 GetRelativePos() { return  m_vRelativePos; }
    Vec3 GetRelativeScale() { return  m_vRelativeScale; }
    Vec3 GetRelativeRotation() { return  m_vRelativeRotation; }

    Vec3 GetWorldPos() { return m_matWorld.Translation(); }
    Vec3 GetWorldScale();
    //Vec3 GetWorldRot();

    void SetAbsolute(bool _bAbsolute) { m_bAbsolute = _bAbsolute; }
    bool IsAbsolute() { return m_bAbsolute; }

    const Matrix& GetWorldMat() { return m_matWorld; }

    Vec3 GetLocalDIR(DIR_TYPE _type) { return m_arrLocalDir[(UINT)_type]; }
    Vec3 GetWorldDir(DIR_TYPE _type) { return m_arrWorldDir[(UINT)_type]; }

public:
    CTransform();
    ~CTransform();
};
