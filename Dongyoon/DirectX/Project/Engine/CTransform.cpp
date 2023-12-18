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

	m_matWorld = XMMatrixIdentity();// ��������� ������ķ� �ʱ�ȭ

	//world matrix in scale
	m_matWorld._11 = m_vRelativeScale.x;
	m_matWorld._22 = m_vRelativeScale.y;
	m_matWorld._33 = m_vRelativeScale.z;


	//������� 4�࿡  x, y, z ��ǥ �ֱ�
	m_matWorld._41 = m_vRelativePos.x;
	m_matWorld._42 = m_vRelativePos.y;
	m_matWorld._43 = m_vRelativePos.z;

}

void CTransform::UpdateData()
{

	tTransform transform = {};
	transform.matWorld = m_matWorld;


	//��ġ������ Trnasform ������ۿ� ������, b0 �������Ϳ� ���ε�
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&transform, 1);
	pCB->UpdateData(0);
}
