#pragma once
#include "CComponent.h"
// =======================================
// CCamera: ViewSpace 이동 및 Projection 담당
// =======================================
// - Space: 카메라 위치를 원점으로, 카메라가 보는 방향을 Z축으로 봄
// - Matrix: world space -(view matrix)-> view space -(projection matrix)-> screen space
// - Camera는 component이므로 여러개 있을 수 있음

enum class PROJ_TYPE
{
    ORTHGRAPHIC,
    PERSEPECTIVE
};

class CCamera :
    public CComponent
{
private:
    PROJ_TYPE m_ProjType;

    // Perspective projection
    float m_FOV;            // 시야각 Field of View

    // Orthographic projection
    float m_Width;
    float m_Scale;          // 배율

    // Both
    float m_AspectRatio;    // 투영 종횡비
    float m_Far;            // 카메라 최대거리

    // Matrix
    Matrix m_matView;
    Matrix m_matProj;

    UINT m_LayerCheck;      // camera가 볼 수 있는 layer 설정 (bit flag)

public:
    virtual void finaltick() override;
    void render();


public:
    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }
    void SetScale(float _Scale) { m_Scale = _Scale; }
    void SetFOV(float _FOV) { m_FOV = _FOV; }
    void SetCameraPriority(int _Priority);
    void LayerCheck(UINT _LayerIdx, bool _bCheck);
    void LayerCheck(const wstring& _strLayerName, bool _bCheck);
    void LayerCheckAll(){ m_LayerCheck = 0xffffffff; }

    PROJ_TYPE GetProjType() { return m_ProjType; }
    float GetScale() { return m_Scale; }
    float GetFOV() { return m_FOV; }
    Matrix& GetViewMat() { return m_matView; }
    Matrix& GetProjMat() { return m_matProj; }

public:
    CCamera();
    ~CCamera();
};

