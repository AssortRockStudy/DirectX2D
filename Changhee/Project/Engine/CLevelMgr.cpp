#include "pch.h"
#include "CLevelMgr.h"

#include "CDevice.h"

#include "CAssetMgr.h"

#include "CLevel.h"

#include "CGameObject.h"

#include "CTransform.h"
#include "CMeshRender.h"
#include "CPlayerScript.h"
#include "CCameraMoveScript.h"

#include "CTexture.h"

CLevelMgr::CLevelMgr()
	:m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if(nullptr!= m_CurLevel)
		delete m_CurLevel;
}


void CLevelMgr::init()
{
	// �ʱ� ���� ����
	m_CurLevel = new CLevel;

	CTexture* pTex = CAssetMgr::GetInst()->Load<CTexture>(L"PlayerTexture", L"texture\\Character.png");
	if (nullptr != pTex)
	{
		pTex->UpdateData(0);
	}



	// Camera Object ����
	CGameObject* pCamObj = new CGameObject;
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);


	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	m_CurLevel->AddObject(pCamObj, 0);

	// GameObject ����
	CGameObject* pObj = nullptr;

	pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CPlayerScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(1000.f, 1000.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	m_CurLevel->AddObject(pObj, 0, false);
}

void CLevelMgr::tick()
{
	if (nullptr == m_CurLevel)
		return;

	// ���� �����ӿ� ��ϵ� ������Ʈ�� clear
	m_CurLevel->clear();


	m_CurLevel->tick();
	m_CurLevel->finaltick();

}

void CLevelMgr::render()
{
	if (nullptr == m_CurLevel)
		return;

	float ClearColor[4] = { 0.3f,0.3f,0.3f,1.f };
	
	CDevice::GetInst()->ClearRenderTarget(ClearColor);

	m_CurLevel->render();

	CDevice::GetInst()->Present();
}
