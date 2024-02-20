#include "pch.h"
#include "CLevelMgr.h"

#include "CDevice.h"
#include "CAssetMgr.h"
#include "CCollisionMgr.h"
#include "CTaskMgr.h"

#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "components.h"
#include "CPlayerScript.h"
#include "CBackgroundScript.h"

#include "CMesh.h"
#include "CGraphicsShader.h" 
#include "CTexture.h"

#include "CSetColorShader.h"

CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_CurLevel)
	{
		delete m_CurLevel;
	}
}


void CLevelMgr::init()
{
	// 머테리얼 로드 테스트
	CAssetMgr::GetInst()->Load<CMaterial>(L"TestMtrl", L"material\\testmtrl.mtrl");


	// 초기 레벨 구성
	m_CurLevel = new CLevel;
	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Background");
	m_CurLevel->GetLayer(2)->SetName(L"Tile");
	m_CurLevel->GetLayer(3)->SetName(L"Player");
	m_CurLevel->GetLayer(4)->SetName(L"Monster");
	m_CurLevel->GetLayer(5)->SetName(L"Light");

	m_CurLevel->GetLayer(31)->SetName(L"UI");

	// 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");
	CCollisionMgr::GetInst()->LayerCheck(L"Monster", L"Monster");
	
	// Main Camera 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);

	pCamObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetCameraPriority(0);
	pCamObj->Camera()->LayerCheckAll();
	// '메인 카메라에 UI는 그리지 마라'라는 뜻
	// 즉, 메인카메라가 움직여도 UI에 해당하는 부분은 영향받지 않는다
	pCamObj->Camera()->LayerCheck(L"UI", false);

	m_CurLevel->AddObject(pCamObj, 0);

	// UI Camera 생성
	pCamObj = new CGameObject;
	pCamObj->SetName(L"UICamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);

	pCamObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetCameraPriority(1);
	pCamObj->Camera()->LayerCheck(L"UI", true);

	m_CurLevel->AddObject(pCamObj, 0);

	// 광원 추가
	CGameObject* pLight = new CGameObject;
	pLight->SetName(L"Light2D");
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	//pLight->Light2D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLight->Light2D()->SetAmbient(Vec3(0.8f, 0.8f, 0.8f));
	//pLight->Light2D()->SetRadius(500.f);
	//pLight->Light2D()->SetAngle(XM_PI / 6.f);
	//pLight->Light2D()->SetDir(Vec3(1.f, 0.f, 0.f));

	m_CurLevel->AddObject(pLight, L"Light");

	// Player 생성
	CGameObject* pObj = nullptr;
	pObj = new CGameObject;
	pObj->SetName(L"PlayerObj");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 300.f));
	pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, -20.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	pObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, 0.f);

	Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(L"PlayerTex", L"texture\\link.png");
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_0, pTex);

	// Particle  생성
	CGameObject* pParticleObj = new CGameObject;
	pParticleObj->SetName(L"Particle");
	pParticleObj->AddComponent(new CTransform);
	pParticleObj->AddComponent(new CParticleSystem);
	pParticleObj->Transform()->SetRelativePos(Vec3(100.f, 0.f, 200.f));
	pObj->AddChild(pParticleObj);

	m_CurLevel->AddObject(pObj, L"Player", false);

	pObj = pObj->Clone();
	pObj->Transform()->SetRelativePos(Vec3(-500.f, 0.f, 500.f));
	m_CurLevel->AddObject(pObj, L"Player", false);

	// background  생성
	CGameObject* pBObj = new CGameObject;
	pBObj->SetName(L"Background");

	pBObj->AddComponent(new CTransform);
	pBObj->AddComponent(new CMeshRender);

	pBObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 600.f));
	pBObj->Transform()->SetRelativeScale(Vec3(1800.f, 800.f, 1.f));

	pBObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pBObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl"));
	pBObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, 0.f);

	pTex = CAssetMgr::GetInst()->Load<CTexture>(L"BackgroundTex", L"texture\\Background.jpg");
	pBObj->MeshRender()->GetMaterial()->SetTexParam(TEX_0, pTex);

	m_CurLevel->AddObject(pBObj, L"Background", false);

	//// Monster Object 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"Monster");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);

	//pObj->Transform()->SetRelativePos(Vec3(500.f, 0.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	//pObj->Collider2D()->SetAbsolute(true);
	//pObj->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
	//pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	//pObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, 0.f);

	//m_CurLevel->AddObject(pObj, L"Monster", false);

	//// 타일 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"TileMap");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CTileMap);

	//pTex = CAssetMgr::GetInst()->Load<CTexture>(L"TileAtlasTex", L"texture\\TILE.bmp");
	//pObj->TileMap()->SetTileAtlas(pTex, Vec2(64.f, 64.f));
	//pObj->TileMap()->SetFace(8, 6);
	//for (int i = 0; i < 6; ++i)
	//{
	//	for (int j = 0; j < 8; ++j)
	//	{
	//		pObj->TileMap()->SetTileIndex(i, j, i * 6 + j);
	//	}
	//}

	//m_CurLevel->AddObject(pObj, L"Tile", false);

	//// PostProcess 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"Distortion");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 200.f));
	//pObj->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 1.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"VCRDistortionMtrl"));

	//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"Noise", L"texture\\noise\\noise_03.jpg"));

	//m_CurLevel->AddObject(pObj, L"Default", false);


	// Level 시작
	//CLevel* pNewLevel = m_CurLevel->Clone();
	//delete m_CurLevel;
	//m_CurLevel = pNewLevel;

	// 레벨 플레이
	m_CurLevel->ChangeState(LEVEL_STATE::STOP);
}

void CLevelMgr::tick()
{
	if (nullptr == m_CurLevel)
	{
		return;
	}

	// 이전 프레임에 등록된 오브젝트들 clear
	m_CurLevel->clear();

	m_CurLevel->tick();
	m_CurLevel->finaltick();
}



void CLevelMgr::ChangeLevelState(LEVEL_STATE _State)
{
	tTask task = {};

	task.Type = TASK_TYPE::CHANGE_LEVELSTATE;
	task.Param_1 = (DWORD_PTR)m_CurLevel;
	task.Param_2 = (DWORD_PTR)_State;

	CTaskMgr::GetInst()->AddTask(task);
}