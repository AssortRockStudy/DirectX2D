#include "pch.h"
#include "CLight2D.h"
#include "CRenderMgr.h"

CLight2D::CLight2D()
	: CComponent(COMPONENT_TYPE::LIGHT2D)
{
}

CLight2D::~CLight2D()
{

}

void CLight2D::finaltick()
{
	CRenderMgr::GetInst()->RegisterLight2D(this);
}