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
	m_matWorld = XMMatrixIdentity(); // 단위행렬
	
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

	// vec3 -> vec4 확장
	// - XMVector3TransformCoord:	w를 1로 확장
	// - XMVector3TransformNormal:	w를 0으로 확장
	for (int i = 0; i < 3; ++i)
	{
		m_arrDir[i] = XMVector3TransformNormal(m_arrDir[i], m_matWorld); // translation 적용 않기 위해 0으로 확장
		m_arrDir[i].Normalize(); // scale 적용 않기 위해 정규화
	}
}

void CTransform::UpdateData()
{
	g_Transform.matWorld = m_matWorld;

	// 위치정보를 Transform Constant Buffer로 보내고, B0 Register에 binding
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_Transform);
	pCB->UpdateData(0);
}
