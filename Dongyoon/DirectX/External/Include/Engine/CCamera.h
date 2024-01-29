#pragma once
#include "CComponent.h"

enum class PROJ_TYPE
{
    ORTHOGRAPHIC, //직교 투영
    PERSPECTIVE, // 원근 투영
};

class CCamera :
    public CComponent
{
private:
    PROJ_TYPE   m_ProjType;

    // 원근투영(Perspective)

    float   m_Fov; // 시야각

    // 직교투영(Orthographic)

    float   m_Width; // 직교투영 가로 길이
    float   m_Scale; // 직교투영 배율

    // Both

    float       m_AspectRatio; // 종횡비, 투영 가로세로비율
    float       m_Far;      //투영 최대 거리

    //변환 행렬
    Matrix      m_matView; // view 행렬
    Matrix      m_matProj; // 투영 행렬

    UINT        m_LayerCheck;

public:
    PROJ_TYPE GetProjType() { return m_ProjType; }
    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }

    float GetScale() { return m_Scale; }
    void SetScale(float _Scale) { m_Scale = _Scale; }

    float GetFov() { return m_Fov; }
    void SetFov(float _Fov) { m_Fov = _Fov; }

    const Matrix& GetViewMat() { return m_matView; }
    const Matrix& GetProjMat() { return m_matProj; }

    void SetCameraPriority(int _Priority);
    void LayerCheck(UINT _LayerIdx, bool _bCheck);
    void LayerCheck(const wstring& _strLayerName, bool _bCheck);
    void LayerCheckAll() { m_LayerCheck = 0xffffffff; }


public:
    virtual void finaltick() override;
    void render();

public:
    CCamera();
    ~CCamera();
};

