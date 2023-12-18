#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
private:
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
    CCamera();
    ~CCamera();
};

