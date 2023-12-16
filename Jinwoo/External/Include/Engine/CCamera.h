#pragma once
#include "CComponent.h"



class CCamera :
    public CComponent
{
private:
    // 원근 투영(Perspective)
    float   m_FOV;          // 시야각

    // 직교 투영(Orthographic)
    float   m_Width;        // 직교투영 가로 길이
    float   m_Scale;        // 직교투영 배율

    // Both (둘 다 해당되는 멤버)
    float   m_AspectRatio;  // 종횡비, 투영 가로세로 비율
    float   m_Far;          // 투영 최대 거리
    
    // 변환 행렬
    Matrix  m_matView;
    Matrix  m_matProj;

public:
    CCamera();
    ~CCamera();
};

