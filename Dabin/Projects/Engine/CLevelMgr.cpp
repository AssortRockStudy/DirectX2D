#include "pch.h"
#include "CDevice.h"
#include "CLevelMgr.h"
#include "CAssetMgr.h"
#include "CCollisionMgr.h"

#include "components.h"
#include "CGameObject.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CTexture.h"

#include "CPlayerScript.h"
#include "CCameraMoveScript.h"

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
	m_CurLevel->GetLayer(5)->SetName(L"Light");
	m_CurLevel->GetLayer(31)->SetName(L"UI");

	// set collision
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");
	CCollisionMgr::GetInst()->LayerCheck(L"Monster", L"Monster");

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

	// Create Light
	CGameObject* pLight = new CGameObject;
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CMeshRender);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetLightColor(Vec3(1.f));
	pLight->Light2D()->SetAmbient(Vec3(0.2f));

	pLight->Transform()->SetRelativePos(Vec3(0.f, 0.f, 200.f));
	m_CurLevel->AddObject(pLight, L"Light");
	
	// Light2
	pLight = new CGameObject;
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CMeshRender);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLight->Light2D()->SetLightColor(Vec3(1.f, 0.3f, 0.3f));
	pLight->Light2D()->SetRadius(300.f);

	pLight->Transform()->SetRelativePos(Vec3(-200.f, 0.f, 200.f));
	m_CurLevel->AddObject(pLight, L"Light");

	// Light3
	pLight = new CGameObject;
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CMeshRender);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLight->Light2D()->SetLightColor(Vec3(0.3f, 1.f, 0.3f));
	pLight->Light2D()->SetRadius(300.f);

	pLight->Transform()->SetRelativePos(Vec3(200.f, 0.f, 200.f));
	m_CurLevel->AddObject(pLight, L"Light");

	// Light4
	pLight = new CGameObject;
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CMeshRender);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::SPOT);
	pLight->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLight->Light2D()->SetAngle(XM_PI / 4);	// 부채꼴 각 설정
	pLight->Light2D()->SetRadius(500.f);

	pLight->Transform()->SetRelativePos(Vec3(0.f, 0.f, 200.f));
	pLight->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, XM_PI / 2.f));
	m_CurLevel->AddObject(pLight, L"Light");

	// Create Background
	Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(L"BackgroundTexture", L"texture\\Background.png");
	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"Background");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 300.f));
	pObj->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMat"));
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

	m_CurLevel->AddObject(pObj, L"Background", false);

	// Create Tilemap
	pObj = new CGameObject();
	pObj->SetName(L"TileMap");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CTileMap);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 299.f));

	Ptr<CTexture> pTileAtlas = CAssetMgr::GetInst()->Load<CTexture>(L"TileAtlas", L"texture\\TILE.bmp");
	pObj->TileMap()->SetAtlas(pTileAtlas, Vec2(64.f, 64.f));

	m_CurLevel->AddObject(pObj, L"Tile", false);

	// Create GameObject
	pTex = CAssetMgr::GetInst()->Load<CTexture>(L"PlayerTexture", L"texture\\Fighter.bmp");
	pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CPlayerScript);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pObj->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));

	pObj->Collider2D()->SetAbsolute(false);
	pObj->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMat"));
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);
	//pObj->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, 1);

	// child
	CGameObject* pChild = new CGameObject;
	pChild->SetName(L"Child");

	pChild->AddComponent(new CTransform);
	pChild->AddComponent(new CMeshRender);

	pChild->Transform()->SetAbsolute(true);
	pChild->Transform()->SetRelativePos(Vec3(100.f, 0.f, 0.f));
	pChild->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

	pChild->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pChild->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMat"));
	
	pObj->AddChild(pChild);

	m_CurLevel->AddObject(pObj, L"Player", false);

	// Monster
	pObj = new CGameObject;
	pObj->SetName(L"Monster");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);

	pObj->Transform()->SetRelativePos(Vec3(200.f, 0.f, 100.f));
	pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(50.f, 50.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMat"));
	
	m_CurLevel->AddObject(pObj, L"Monster", false);

	// UI Object Create
	pObj = new CGameObject;
	pObj->SetName(L"UI");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);

	pObj->Transform()->SetRelativePos(Vec3(-590, 310.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"UIMat"));
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);

	m_CurLevel->AddObject(pObj, L"UI", false);

	// PostProcess Object Create
	pObj = new CGameObject;
	pObj->SetName(L"Distortion");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 200.f));
	pObj->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DistortionMat"));
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"NoiseTex", L"texture\\noise\\noise_03.jpg"));

	m_CurLevel->AddObject(pObj, L"Default", false);
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