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
	m_vRelativePos;
	m_vRelativeScale;
	m_vRelativeRotation;

	m_matWorld = XMMatrixIdentity();// 월드행렬을 단위행렬로 초기화

	//world matrix in scale
	m_matWorld._11 = m_vRelativeScale.x;
	m_matWorld._22 = m_vRelativeScale.y;
	m_matWorld._33 = m_vRelativeScale.z;


	//월드행렬 4행에  x, y, z 좌표 넣기
	m_matWorld._41 = m_vRelativePos.x;
	m_matWorld._42 = m_vRelativePos.y;
	m_matWorld._43 = m_vRelativePos.z;

}

void CTransform::UpdateData()
{

	tTransform transform = {};
	transform.matWorld = m_matWorld;


	//위치정보를 Trnasform 상수버퍼에 보내고, b0 레지스터에 바인딩
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&transform, 1);
	pCB->UpdateData(0);
}
