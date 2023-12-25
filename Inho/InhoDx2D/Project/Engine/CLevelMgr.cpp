#include "pch.h"
#include "CLevelMgr.h"

#include "CDevice.h"
#include "CAssetMgr.h"

#include "CLevel.h"
#include "CGameObject.h"
#include "components.h"
#include "CPlayerScript.h"
#include "CCameraMoveScript.h"

#include "CMesh.h"
#include "CGraphicsShader.h"
#include "CTexture.h"

CLevelMgr::CLevelMgr() 
	:m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr() {

}

void CLevelMgr::init()
{
	m_CurLevel = new CLevel;



	CTexture* pTex = CAssetMgr::GetInst()->Load<CTexture>(L"PlayerTexture", L"texture\\Character.png");
	if (nullptr != pTex) {
		pTex->UpdateData(0);
	}



	CGameObject* pCamObj = new CGameObject;
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	m_CurLevel->AddObject(pCamObj, 0);


	CGameObject* pObj = nullptr;

	pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CPlayerScript);

	pObj->Transform()->SetRelativePos(Vec3(0.0f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicsShader>(L"Std2dShader"));


	CGameObject* pChildObj = new CGameObject;
	pChildObj->SetName(L"Child");

	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);

	pChildObj->Transform()->SetRelativePos(Vec3(20.0f, 0.f, -10.f));
	pChildObj->Transform()->SetRelativeScale(Vec3(100.f, 150.f, 1.f));	
	pChildObj->Transform()->SetAbsolute(true);

	pChildObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicsShader>(L"Std2dShader"));

	pObj->AddChild(pChildObj);

	m_CurLevel->AddObject(pObj, 0);
	//m_CurLevel->AddObject(pChildObj, 0);

}

void CLevelMgr::tick()
{
	if (nullptr == m_CurLevel) {
		return;
	}
	m_CurLevel->tick();
	m_CurLevel->finaltick();
}

void CLevelMgr::render()
{
	if (nullptr == m_CurLevel) {
		return;
	}

	float ClearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearRenderTarget(ClearColor);

	m_CurLevel->render();

	CDevice::GetInst()->Present();
}
