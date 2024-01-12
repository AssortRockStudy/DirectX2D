#include "pch.h"
#include "CRenderMgr.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"

void CRenderMgr::init()
{
	m_pDbgObj = new CGameObject;
	m_pDbgObj->AddComponent(new CTransform);
	m_pDbgObj->AddComponent(new CMeshRender);
}