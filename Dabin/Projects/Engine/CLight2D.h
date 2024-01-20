#pragma once
#include "CComponent.h"
// =======================================
// CLight2D: 광원이 상속하는 parent class
// =======================================

class CLight2D :
    public CComponent
{
private:
    tLightInfo  m_Info;

public:
    virtual void finaltick() override;

public:
    const tLightInfo& GetLightInfo() { return m_Info; }

    void SetLightType(LIGHT_TYPE _type) { m_Info.LightType = (int)_type; }
    void SetLightColor(Vec3 _vColor) { m_Info.vColor = _vColor; }
    void SetSpecular(Vec3 _vSpec) { m_Info.vSpecular = _vSpec; }
    void SetAmbient(Vec3 _vAmb) { m_Info.vAmbient = _vAmb; }
    void SetRadius(float _fRadius) { m_Info.fRadius = _fRadius; }
    void SetAngle(float _fAngle) { m_Info.fAngle = _fAngle; }
    LIGHT_TYPE GetLightType() { return (LIGHT_TYPE)m_Info.LightType; }
    Vec4 GetLightColor(Vec3 _vColor) { return m_Info.vColor; }
    Vec4 GetSpecular(Vec3 _vSpec) { return m_Info.vSpecular; }
    Vec4 GetAmbient(Vec3 _vAmb) { return m_Info.vAmbient; }
    float GetRadius() { return m_Info.fRadius; }
    float GetAngle() { return m_Info.fAngle; }

public:
    CLight2D();
    ~CLight2D();
};

