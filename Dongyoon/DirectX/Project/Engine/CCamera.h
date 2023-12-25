#pragma once
#include "CComponent.h"

enum class PROJ_TYPE
{
    ORTHOGRAPHIC, //���� ����
    PERSPECTIVE, // ���� ����
};

class CCamera :
    public CComponent
{
private:
    PROJ_TYPE   m_ProjType;

    // ��������(Perspective)

    float   m_Fov; // �þ߰�

    // ��������(Orthographic)

    float   m_Width; // �������� ���� ����
    float   m_Scale; // �������� ����

    // Both

    float       m_AspectRatio; // ��Ⱦ��, ���� ���μ��κ���
    float       m_Far;      //���� �ִ� �Ÿ�

    //��ȯ ���
    Matrix      m_matView; // view ���
    Matrix      m_matProj; // ���� ���

public:
    PROJ_TYPE GetProjType() { return m_ProjType; }
    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }

    float GetScale() { return m_Scale; }
    void SetScale(float _Scale) { m_Scale = _Scale; }

    float GetFov() { return m_Fov; }
    void SetFov(float _Fov) { m_Fov = _Fov; }

public:
    virtual void finaltick() override;

public:
    CCamera();
    ~CCamera();
};

