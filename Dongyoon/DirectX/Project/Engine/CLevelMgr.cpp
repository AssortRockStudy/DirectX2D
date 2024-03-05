#include "pch.h"
#include "CLevelMgr.h"

#include "CDevice.h"
#include "CAssetMgr.h"

#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "components.h"
#include "CPlayerScript.h"
#include "CCameraMoveScript.h"

#include "CMesh.h"
#include "CGraphicsShader.h"
#include "CTexture.h"
#include "CCollisionMgr.h"
#include "CBackgroundScript.h"

#include "CSetColorShader.h"

CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_CurLevel)
		delete m_CurLevel;
}

void CLevelMgr::init()
{
	// 초기 레벨 구성하기
	m_CurLevel = new CLevel;
	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Background");
	m_CurLevel->GetLayer(2)->SetName(L"Tile");
	m_CurLevel->GetLayer(3)->SetName(L"Player");
	m_CurLevel->GetLayer(4)->SetName(L"Monster");
	m_CurLevel->GetLayer(5)->SetName(L"Light");
	m_CurLevel->GetLayer(6)->SetName(L"Tile");

	m_CurLevel->GetLayer(31)->SetName(L"UI");
	

	//ComputeShader 테스트
	//사용할 텍스쳐 생성
	Ptr<CTexture> pTestTex = CAssetMgr::GetInst()->CreateTexture(L"TestTex", 1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM
																, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);

	Ptr<CSetColorShader> pCS = (CSetColorShader*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"SetColorShader").Get();
	pCS->SetColor(Vec3(1.f, 0.f, 0.f));
	pCS->SetTargetTexture(pTestTex);
	pCS->Execute();

	tPixel* pPixel = pTestTex->GetPixels();
	tPixel pixel = pPixel[pTestTex->GetWidth() * 1 + 5];


	// 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");
	CCollisionMgr::GetInst()->LayerCheck(L"Monster", L"Monster");


	// Main Camera Object 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetCameraPriority(0);
	pCamObj->Camera()->LayerCheckAll();
	pCamObj->Camera()->LayerCheck(L"UI", false);

	m_CurLevel->AddObject(pCamObj, 0);


	pCamObj = new CGameObject;
	pCamObj->SetName(L"UICamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetCameraPriority(1);
	pCamObj->Camera()->LayerCheck(L"UI", true);

	m_CurLevel->AddObject(pCamObj, 0);

	// 전역 광원 추가
	CGameObject* pLight = new CGameObject;
	pLight->SetName(L"Directional Light");
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CMeshRender);
	pLight->AddComponent(new CLight2D);
	
	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetAmbient(Vec3(0.8f, 0.8f, 0.8f));
	
	m_CurLevel->AddObject(pLight, L"Light");
	

	CGameObject* pObj = nullptr;

	// Background Object 생성

	pObj = new CGameObject;
	pObj->SetName(L"Background");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CBackgroundScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 600.f));
	pObj->Transform()->SetRelativeScale(Vec3(1600.f, 800.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl"));

	Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(L"BackgroundTex", L"texture\\Background.jpg");
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_0, pTex);

	m_CurLevel->AddObject(pObj, L"Background", false);

	// Player Object 생성



	pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	pObj->MeshRender()->GetMaterial()->SetScalarParam(FLOAT_0, 0.f);
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"PlayerTexture", L"texture\\Fighter.bmp"));

	pObj->Animator2D()->Play(L"Explosion");

	m_CurLevel->AddObject(pObj, L"Player", false);

	//Particle Object

	pObj = new CGameObject;
	pObj->SetName(L"Particle");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CParticleSystem);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));

	m_CurLevel->AddObject(pObj, L"Default", false);

	// Level 시작
	m_CurLevel->begin();
}

void CLevelMgr::tick()
{
	if (nullptr == m_CurLevel)
		return;

	m_CurLevel->clear();

	m_CurLevel->tick();
	m_CurLevel->finaltick();
}

