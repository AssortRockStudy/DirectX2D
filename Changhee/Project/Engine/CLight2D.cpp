#include "pch.h"
#include "CLight2D.h"

#include "CRenderMgr.h"
#include "CTransform.h"

CLight2D::CLight2D()
	:CComponent(COMPONENT_TYPE::LIGHT2D)
{
}

CLight2D::~CLight2D()
{
}

void CLight2D::finaltick()
{
	// 월드 위치값을 LightInfo 맴버에 갱신해놓는다.
	Vec3 vWorldPos = Transform()->GetWorldPos();
	m_Info.vWorldPos = vWorldPos;

	CRenderMgr::GetInst()->RegisterLight2D(this);
}

