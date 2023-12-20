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

	m_matWorld = XMMatrixIdentity();// 월드행렬을 단위행렬로 초기화

	Matrix matScale = XMMatrixScaling(m_vRelativeScale.x, m_vRelativeScale.y, m_vRelativeScale.z);

	Matrix matRotX = XMMatrixRotationX(m_vRelativeRotation.x);
	Matrix matRotY = XMMatrixRotationY(m_vRelativeRotation.y);
	Matrix matRotZ = XMMatrixRotationZ(m_vRelativeRotation.z);

	Matrix matTranslation = XMMatrixTranslation(m_vRelativePos.x, m_vRelativePos.y, m_vRelativePos.z);

	m_matWorld = matScale * matRotX * matRotY * matRotZ * matTranslation;

	//물체의 방향값을 다시 계산
	m_arrDir[(UINT)DIR_TYPE::RIGHT] = Vec3(1.f, 0.f, 0.f);
	m_arrDir[(UINT)DIR_TYPE::UP] = Vec3(0.f, 1.f, 0.f);
	m_arrDir[(UINT)DIR_TYPE::FRONT] = Vec3(0.f, 0.f, 1.f);

	//Vec3를 Vec4로 바꿔서 행렬을 적용시켜야한다.
	//XMVector3TransformCoord - w를 1로 확장
	//XMVector3TransformNormal - w를 0으로 확장
	//mul(float4(_in.vPos, 1 or 0), g_matWorld;   적용받을 상태행렬의 이동여부 결정

	for (int i = 0; i < 3; ++i)
	{
		//m_matWorld 행렬에 크기정보가 있을 수 있기 때문에, 다시 길이를 1로 정규화
		m_arrDir[i] = XMVector3TransformNormal(m_arrDir[i], m_matWorld);
		m_arrDir[i].Normalize();
	}
}

void CTransform::UpdateData()
{

	g_Transform.matWorld = m_matWorld;


	//위치정보를 Trnasform 상수버퍼에 보내고, b0 레지스터에 바인딩
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_Transform, 1);
	pCB->UpdateData(0);
}
