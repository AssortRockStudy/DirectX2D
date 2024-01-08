#pragma once
#include "CComponent.h"
class CTransform :
    public CComponent
{
private:
    Vec3 m_vRelativePos;
    Vec3 m_vRelativeScale;
    Vec3 m_vRealtiveRotation;
    Vec3 m_arrLocalDir[3];
    Vec3 m_arrWorldDir[3];
    Matrix m_matWorld;
    bool m_bAbsolute;

public:
    virtual void finaltick() override;
    virtual void UpdateData() override;

public:
    void SetRelativePos(Vec3 _Pos) { m_vRelativePos = _Pos; }
    void SetRelativeScale(Vec3 _Scale) { m_vRelativeScale = _Scale; }
    void SetRelativeRotation(Vec3 _Rotation) { m_vRealtiveRotation = _Rotation; }
    void SetWorldMat(const Matrix _matWorld) { m_matWorld = _matWorld; }
    Vec3 GetRelativePos() { return m_vRelativePos; }
    Vec3 GetRelativeScale() { return m_vRelativeScale; }
    Vec3 GetRelativeRotation() { return m_vRealtiveRotation; }
    Vec3 GetWorldPos() { return m_matWorld.Translation(); }
    Vec3 GetWorldScale();
    const Matrix& GetWorldMat() { return m_matWorld; }
    Vec3 GetLocalDir(DIR_TYPE _type) { return m_arrLocalDir[(UINT)_type]; }
    Vec3 GetWorldDir(DIR_TYPE _type) { return m_arrWorldDir[(UINT)_type]; }

    void SetAbsolute(bool _bAbsolute) { m_bAbsolute = _bAbsolute; }

public:
    CTransform();
    ~CTransform();
};

