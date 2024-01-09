#pragma once
#include "CComponent.h"


class CLight2D :
    public CComponent
{
private:
    tLightInfo      m_Info;

public:
    const tLightInfo& GetLightInfo() { return m_Info; }

    void SetLightColor(Vec3 _vColor) { m_Info.vColor = _vColor; }
    void SetSpecular(Vec3 _Specular) { m_Info.vSpecular = _Specular; }
    void SetAmbient(Vec3 _Ambient) { m_Info.vAmbient = _Ambient; }

    Vec4 GetLightColor() { return m_Info.vColor; }
    Vec4 GetSpecular() { return m_Info.vSpecular; }
    Vec4 GetAmbient() { return m_Info.vAmbient; }

    void SetLightType(LIGHT_TYPE _type);
    void SetRadius(float _Radius);
    void SetAngle(float _Angle);

    LIGHT_TYPE GetLightType() { return (LIGHT_TYPE)m_Info.LightType; }
    float GetRadius() { return m_Info.fRadius; }
    float GetAngle() { return m_Info.fAngle; }

public:
    virtual void finaltick() override;

public:
    CLight2D();
    ~CLight2D();
};

