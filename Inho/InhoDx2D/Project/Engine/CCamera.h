#pragma once
#include "CComponent.h"

class CCamera :
    public CComponent
{
private:
    float m_FOV;

    float m_Width;
    float m_Scale;

    float m_AspectRatio;
    float m_Far;

    Matrix m_matView;
    Matrix m_matProj;

public:
    virtual void finaltick() override;

public:
    CCamera();
    ~CCamera();

};

