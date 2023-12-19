#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
private:
    // ��������
    float m_FOV;          // �þ� ��

    // ��������
    float m_Width;        // �������� ���� ����
    float m_Scale;        // �������� ����

    float m_AspectRatio;  // ��Ⱦ��, ���� ���μ��� ����
    float m_Far;          // ���� �ִ� �Ÿ�

    // ��ȯ ���
    Matrix m_matView;
    Matrix m_matProj;

public:
    CCamera();
    ~CCamera();
};

