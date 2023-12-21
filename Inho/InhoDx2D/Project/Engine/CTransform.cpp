#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"

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
	m_matWorld = XMMatrixIdentity();

	Matrix matScale = XMMatrixScaling(m_vRelativeScale.x, m_vRelativeScale.y, m_vRelativeScale.z);

	Matrix matRotX = XMMatrixRotationX(m_vRelativeRotation.x);
	Matrix matRotY = XMMatrixRotationY(m_vRelativeRotation.y);
	Matrix matRotZ = XMMatrixRotationZ(m_vRelativeRotation.z);

	Matrix matTranslation = XMMatrixTranslation(m_vRelativePos.x, m_vRelativePos.y, m_vRelativePos.z);

	m_matWorld = matScale * matRotX * matRotY * matRotZ * matTranslation;

	m_arrDir[(UINT)DIR_TYPE::RIGHT] = Vec3(1.f, 0.f, 0.f);
	m_arrDir[(UINT)DIR_TYPE::UP] = Vec3(0.f, 1.f, 0.f);
	m_arrDir[(UINT)DIR_TYPE::FRONT] = Vec3(0.f, 0.f, 1.f);

	for (int i = 0; i < 3; i++) {
		m_arrDir[i] = XMVector3TransformNormal(m_arrDir[i], m_matWorld);
		m_arrDir[i].Normalize();
	}
}

void CTransform::UpdateData()
{
	
	g_Transform.matWorld = m_matWorld;
	
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_Transform);
	pCB->UpdateData(0);
}
