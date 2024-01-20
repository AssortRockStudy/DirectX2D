#include "pch.h"
#include "CCollider2D.h"
#include "CTransform.h"
#include "CScript.h"

CCollider2D::CCollider2D()
	: CComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_Type(COLLIDER2D_TYPE::RECT)
	, m_bAbsolute(false)
	, m_CollisionCount(0)
{
}

CCollider2D::~CCollider2D()
{
}

void CCollider2D::finaltick()
{
	// 1. matrix calculate
	// collider local matrix
	m_matColWorld = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
	m_matColWorld *= XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);

	// owner's world matrix
	const Matrix& matObjWorld = Transform()->GetWorldMat();

	// collder world matrix
	if (m_bAbsolute)
	{
		Vec3 vWorldScale = Transform()->GetWorldScale();
		Matrix matWorldScaleInv = XMMatrixScaling(vWorldScale.x, vWorldScale.y, vWorldScale.z);
		matWorldScaleInv = XMMatrixInverse(nullptr, matWorldScaleInv);

		m_matColWorld = m_matColWorld * matWorldScaleInv * matObjWorld;
	}
	else
		m_matColWorld *= matObjWorld;

	// 2. render color
	if (m_CollisionCount == 0)
		GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(0.f, 1.f, 0.f), false);
	else
		GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(1.f, 0.f, 0.f), false);
}

void CCollider2D::BeginOverlap(CCollider2D* _OtherCollider)
{
	++m_CollisionCount;

	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
		vecScript[i]->BeginOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}

void CCollider2D::Overlap(CCollider2D* _OtherCollider)
{
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
		vecScript[i]->Overlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}

void CCollider2D::EndOverlap(CCollider2D* _OtherCollider)
{
	--m_CollisionCount;
	
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
		vecScript[i]->EndOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}
