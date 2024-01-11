#include "pch.h"
#include "CRenderMgr.h"

#include "CStructuredBuffer.h"

#include "CTimeMgr.h"

#include "CDevice.h"
#include "CCamera.h"
#include "CMeshRender.h"
#include "CAssetMgr.h"
#include "CTransform.h"

CRenderMgr::CRenderMgr()
	: m_Light2DBuffer(nullptr)
	, m_DebugObj(nullptr)
	, m_bDebugPosition(true)
{

}

CRenderMgr::~CRenderMgr()
{
	if (nullptr != m_DebugObj)
		delete m_DebugObj;

	if (nullptr != m_Light2DBuffer)
		delete m_Light2DBuffer;

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
			m_DebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh_Debug"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_DebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh_Debug"));
			break;
		case DEBUG_SHAPE::CROSS:
			m_DebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CrossMesh"));
			break;
		case DEBUG_SHAPE::CUBE:
			m_DebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CubeMesh"));
			break;
		case DEBUG_SHAPE::SPHERE:
			m_DebugObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"SphereMesh"));
			break;
		default:
			break;
		}

		m_DebugObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DebugShapeMtrl"));
		m_DebugObj->MeshRender()->GetMaterial()->SetScalarParam(VEC4_0, (*iter).vColor);

		D3D11_PRIMITIVE_TOPOLOGY PrevTopology = m_DebugObj->MeshRender()->GetMaterial()->GetShader()->GetTopology();
		if (DEBUG_SHAPE::CROSS == (*iter).eShape)
		{
			m_DebugObj->MeshRender()->GetMaterial()->GetShader()->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
		}

		m_DebugObj->Transform()->SetWorldMat((*iter).matWorld);
		m_DebugObj->Transform()->UpdateData();

		m_DebugObj->render();

		m_DebugObj->MeshRender()->GetMaterial()->GetShader()->SetTopology(PrevTopology);

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

	// 동일한 우선순위의 카메라가 이미 존재하면 assert
	assert(nullptr == m_vecCam[_Idx]);

	m_vecCam[_Idx] = _Cam;
}