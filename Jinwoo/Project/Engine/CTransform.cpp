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

// tick이 끝나고 확정된 m_vRelativePos, m_vRelativeScale, m_vRelativeRotation 정보를
// 행렬에 집어넣는다
void CTransform::finaltick()
{
	// 월드 매트릭스를 단위행렬로 초기화
	m_matWorld = XMMatrixIdentity();

	m_matWorld._11 = m_vRelativeScale.x;
	m_matWorld._22 = m_vRelativeScale.y;
	m_matWorld._33 = m_vRelativeScale.z;

	// 월드 매트릭스 4행에 옮기고 싶은 위치를 넣는다
	m_matWorld._41 = m_vRelativePos.x;
	m_matWorld._42 = m_vRelativePos.y;
	m_matWorld._43 = m_vRelativePos.z;
}

void CTransform::UpdateData()
{
	tTransform Transform = {};
	Transform.matWorld = m_matWorld;

	// 위치정보를 Trnasform 상수버퍼에 보내고, B0 레지스터에 바인딩
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&Transform);
	pCB->UpdateData(0);
}