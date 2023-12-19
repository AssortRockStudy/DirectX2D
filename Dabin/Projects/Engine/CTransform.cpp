#include "pch.h"
#include "CTransform.h"
#include "CConstBuffer.h"
#include "CDevice.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_vRelativeScale(Vec3(1.f, 1.f, 1.f))
{
}

CTransform::~CTransform()
{
}

void CTransform::finaltick()
{
	// --------------------------
	// Transformation Matrix
	// --------------------------
	m_matWorld = XMMatrixIdentity(); // �������
	
	// scale
	m_matWorld._11 = m_vRelativeScale.x;
	m_matWorld._22 = m_vRelativeScale.y;
	m_matWorld._33 = m_vRelativeScale.z;
	Matrix matScale = XMMatrixScaling(m_vRelativeScale.x, m_vRelativeScale.y, m_vRelativeScale.z);

	// rotate
	Matrix matRotX = XMMatrixRotationX(m_vRelativeRotation.x);
	Matrix matRotY = XMMatrixRotationY(m_vRelativeRotation.y);
	Matrix matRotZ = XMMatrixRotationZ(m_vRelativeRotation.z);

	// translation
	m_matWorld._41 = m_vRelativePos.x;
	m_matWorld._42 = m_vRelativePos.y;
	m_matWorld._43 = m_vRelativePos.z;
	Matrix matTranslation = XMMatrixTranslation(m_vRelativePos.x, m_vRelativePos.y, m_vRelativePos.z);

	m_matWorld = matScale * matRotX * matRotY * matRotZ * matTranslation;

	// --------------------------
	// Object Direction Vector
	// --------------------------
	m_arrDir[(UINT)DIR_TYPE::RIGHT] = Vec3(1.f, 0.f, 0.f);
	m_arrDir[(UINT)DIR_TYPE::UP] = Vec3(0.f, 1.f, 0.f);
	m_arrDir[(UINT)DIR_TYPE::FRONT] = Vec3(0.f, 0.f, 1.f);

	// vec3 -> vec4 Ȯ��
	// - XMVector3TransformCoord:	w�� 1�� Ȯ��
	// - XMVector3TransformNormal:	w�� 0���� Ȯ��
	for (int i = 0; i < 3; ++i)
	{
		m_arrDir[i] = XMVector3TransformNormal(m_arrDir[i], m_matWorld); // translation ���� �ʱ� ���� 0���� Ȯ��
		m_arrDir[i].Normalize(); // scale ���� �ʱ� ���� ����ȭ
	}
}

void CTransform::UpdateData()
{
	g_Transform.matWorld = m_matWorld;

	// ��ġ������ Transform Constant Buffer�� ������, B0 Register�� binding
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_Transform);
	pCB->UpdateData(0);
}
