#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
private:
    // 원근투영
    float m_FOV;          // 시야 각

    // 직교투영
    float m_Width;        // 직교투영 가로 길이
    float m_Scale;        // 직교투영 배율

    float m_AspectRatio;  // 종횡비, 투영 가로세로 비율
    float m_Far;          // 투영 최대 거리

    // 변환 행렬
    Matrix m_matView;
    Matrix m_matProj;

public:
    CCamera();
    ~CCamera();
};

