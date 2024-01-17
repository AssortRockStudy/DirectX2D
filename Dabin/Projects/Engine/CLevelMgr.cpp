#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGameObject.h"
#include "components.h"
#include "CPlayerScript.h"
#include "CAssetMgr.h"
#include "CDevice.h"
#include "CCamera.h"
#include "CCameraMoveScript.h"
#include "CTexture.h"
#include "CLayer.h"

CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (m_CurLevel)
		delete m_CurLevel;
}

void CLevelMgr::init()
{
	// 초기 레벨 생성
	m_CurLevel = new CLevel;
	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Background");
	m_CurLevel->GetLayer(2)->SetName(L"Tile");
	m_CurLevel->GetLayer(3)->SetName(L"Player");
	m_CurLevel->GetLayer(4)->SetName(L"Monster");
	m_CurLevel->GetLayer(31)->SetName(L"UI");

	// Create Main Camera
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetCameraPriority(0);
	pCamObj->Camera()->LayerCheckAll();
	pCamObj->Camera()->LayerCheck(L"UI", false);

	m_CurLevel->AddObject(pCamObj, L"Default", false);

	// Create UI Camera
	pCamObj = new CGameObject;
	pCamObj->SetName(L"UICamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3());

	pCamObj->Camera()->SetCameraPriority(1);
	pCamObj->Camera()->LayerCheck(L"UI", true);
	pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);

	m_CurLevel->AddObject(pCamObj, L"Default", false);

	// Texture Load
	Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(L"PlayerTexture", L"texture\\Fighter.bmp");
	
	// Create GameObject
	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CPlayerScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pObj->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMat"));
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);
	//pObj->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 1);
	
	// child
	CGameObject* pChild = new CGameObject;
	pChild->SetName(L"Child");

	pChild->AddComponent(new CTransform);
	pChild->AddComponent(new CMeshRender);

	pChild->Transform()->SetRelativePos(Vec3(100.f, 0.f, 0.f));
	pChild->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));
	pChild->Transform()->SetAbsolute(true);

	pChild->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pChild->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMat"));
	
	pObj->AddChild(pChild);

	m_CurLevel->AddObject(pObj, L"Default", false);

	// UI Object Create
	pObj = new CGameObject;
	pObj->SetName(L"UI");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);

	pObj->Transform()->SetRelativePos(Vec3(-590, 310.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMat"));

	m_CurLevel->AddObject(pObj, L"UI", false);

	GamePlayStatic::DrawDebugRect(Vec3(100.f, 0.f, 100.f), Vec3(200.f, 200.f, 1.f), Vec3(0.f, 0.f, 0.f), Vec3(1.f, 1.f, 1.f), true, 20);
}

void CLevelMgr::tick()
{
	if (!m_CurLevel)
		return;

	// 이전 프레임에 등록된 m_vecObjects clear (삭제 등의 이유로 매 프래임마다 새로 등록)
	m_CurLevel->clear(); 

	m_CurLevel->tick();
	m_CurLevel->finaltick();
}