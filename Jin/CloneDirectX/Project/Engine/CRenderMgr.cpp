#include "pch.h"
#include "CRenderMgr.h"


#include "CDevice.h"
#include "CCamera.h"
#include "CMeshRender.h"
#include "CAssetMgr.h"
#include "CTransform.h"
#include "CTimeMgr.h"

CRenderMgr::CRenderMgr()
	: m_pDebugObj(nullptr)
{

}
CRenderMgr::~CRenderMgr()
{
	if (nullptr != m_pDebugObj)
		delete m_pDebugObj;
}

void CRenderMgr::tick()
{
	Vec4 vClearColor = Vec4(0.3f, 0.3f, 0.3f, 1.f);
	CDevice::GetInst()->ClearRenderTarget(vClearColor);

	render();

	render_debug();

	CDevice::GetInst()->Present();
}

void CRenderMgr::render()
{
	for (size_t i = 0; i < m_vecCam.size(); ++i)
	{
		m_vecCam[i]->render();
	}
}

void CRenderMgr::render_debug()
{
	g_Transform.matView = m_vecCam[0]->GetViewMat();
	g_Transform.matProj = m_vecCam[0]->GetProjMat();

	list<tDebugShapeInfo>::iterator iter = m_DbgShapeInfo.begin();
	for (; iter != m_DbgShapeInfo.end();)
	{
		switch ((*iter).eShape)
		{
		case DEBUG_SHAPE::RECT:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh_Debug"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh_Debug"));
			break;
		case DEBUG_SHAPE ::CROSS:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CrossMesh"));
			break;
		case DEBUG_SHAPE::CUBE:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CubeMesh"));
			break;
		case DEBUG_SHAPE::SPHERE:
			m_pDebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"SphereMesh"));
			break;
		default:
			break;
		}

		m_pDebugObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DebugShapeMtrl"));
		m_pDebugObj->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, (*iter).vColor);
		
		D3D11_PRIMITIVE_TOPOLOGY PrevTopology = m_pDebugObj->MeshRender()->GetMaterial()->GetShader()->GetTopology();
		if (DEBUG_SHAPE::CROSS == (*iter).eShape)
			m_pDebugObj->MeshRender()->GetMaterial()->GetShader()->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);

		m_pDebugObj->Transform()->SetWorldMat((*iter).matWorld);
		m_pDebugObj->Transform()->UpdateData();

		m_pDebugObj->render();

		m_pDebugObj->MeshRender()->GetMaterial()->GetShader()->SetTopology(PrevTopology);

		(*iter).fLifeTime += DT;
		if ((*iter).fDuration <= (*iter).fLifeTime)
		{
			iter = m_DbgShapeInfo.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}


void CRenderMgr::RegisterCamera(CCamera* _Cam, int _Idx)
{
	if (m_vecCam.size() <= _Idx + 1)
	{
		m_vecCam.resize(_Idx + 1);
	}

	assert(nullptr == m_vecCam[_Idx]);

	m_vecCam[_Idx] = _Cam;
}