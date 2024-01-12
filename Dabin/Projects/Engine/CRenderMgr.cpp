#include "pch.h"
#include "CRenderMgr.h"
#include "CDevice.h"
#include "CCamera.h"
#include "CMeshRender.h"
#include "CAssetMgr.h"
#include "CTransform.h"

CRenderMgr::CRenderMgr()
	: m_vecCam{}
	, m_DbgShapeInfo {}
	, m_pDbgObj(nullptr)
{

}

CRenderMgr::~CRenderMgr()
{
	if (m_pDbgObj)
		delete m_pDbgObj;
}

void CRenderMgr::tick()
{
	// buffer init
	float ClearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearRenderTarget(ClearColor);

	// rendering
	render();
	render_debug();

	// drawing (buffer show)
	CDevice::GetInst()->Present();
}

void CRenderMgr::render()
{
	for (size_t i = 0; i < m_vecCam.size(); ++i)
		m_vecCam[i]->render();
}

void CRenderMgr::render_debug()
{
	if (m_vecCam.empty())
		return;

	// TODO : 일단 0번 카메라로 지정한 듯? 나중에 고쳐야 함
	g_Transform.matView = m_vecCam[0]->GetViewMat();
	g_Transform.matProj = m_vecCam[0]->GetProjMat();

	for (const tDebugShapeInfo& it : m_DbgShapeInfo)
	{
		// 보유한 Debug obj마다 type 별로 transform, mesh 바꿔가며 render해줌
		switch (it.ShapeType)
		{
		case DEBUG_SHAPE::RECT:
			m_pDbgObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_pDbgObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh"));
			break;
		case DEBUG_SHAPE::CUBE:
			m_pDbgObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CubeMesh"));
			break;
		case DEBUG_SHAPE::SPHERE:
			m_pDbgObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"SphereMesh"));
			break;
		}

		m_pDbgObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DebugShapeMat"));
		m_pDbgObj->Transform()->SetWorldMat(it.matWorld);
		m_pDbgObj->Transform()->UpdatePipeline();
		m_pDbgObj->render();
	}

}

void CRenderMgr::RegisterCamera(CCamera* _Cam, int _idx)
{
	if (m_vecCam.size() <= _idx + 1)
		m_vecCam.resize(_idx + 1);

	assert(!m_vecCam[_idx]);
	m_vecCam[_idx] = _Cam;
}
