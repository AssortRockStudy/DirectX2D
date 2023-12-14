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

}

void CTransform::UpdateData()
{
	tTransform Transform = {};
	Transform.vWorldPos = m_vRelativePos;
	Transform.vWorldScale = m_vRelativeScale;

	// 위치정보를 Trnasform 상수버퍼에 보내고, B0 레지스터에 바인딩
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&Transform);
	pCB->UpdateData(0);
}