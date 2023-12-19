#pragma once
#include "CComponent.h"
// =======================================
// CCamera: ViewSpace �̵� �� Projection ���
// =======================================
// - Space: ī�޶� ��ġ�� ��������, ī�޶� ���� ������ Z������ ��
// - Matrix: world space -(view matrix)-> view space -(projection matrix)-> screen space

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
    float m_FOV;            // �þ߰� Field of View

    // Orthographic projection
    float m_Width;
    float m_Scale;          // ����

    // Both
    float m_AspectRatio;    // ���� ��Ⱦ��
    float m_Far;            // ī�޶� �ִ�Ÿ�

    // Matrix
    Matrix m_matView;
    Matrix m_matProj;

public:
    virtual void finaltick() override;

public:
    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }
    void SetScale(float _Scale) { m_Scale = _Scale; }
    void SetFOV(float _FOV) { m_FOV = _FOV; }

    PROJ_TYPE GetProjType() { return m_ProjType; }
    float GetScale() { return m_Scale; }
    float GetFOV() { return m_FOV; }

public:
    CCamera();
    ~CCamera();
};

