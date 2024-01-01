#include "pch.h"
#include "Test.h"

#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"

#include "CGameObject.h"

#include "CMesh.h"
#include "CGraphicsShader.h"

#include "CTransform.h"
#include "CMeshRender.h"

#include "CPlayerScript.h"

vector<CGameObject*>	g_vecObj;


int TestInit()
{
	// GameObject 1鯵 持失
	// GameObject 持失
	CGameObject* pObj = nullptr;

	pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CPlayerScript);

	pObj->Transform()->SetRelativePos(Vec3(-0.5f, 0.f, 0.f));
	pObj->Transform()->SetRelativeScale(Vec3(1.5f, 1.5f, 1.5f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicsShader>(L"Std2DShader"));

	g_vecObj.push_back(pObj);



	return S_OK;
}

void Tick()
{
	for (size_t i = 0; i < g_vecObj.size(); ++i)
	{
		g_vecObj[i]->tick();
	}

	for (size_t i = 0; i < g_vecObj.size(); ++i)
	{
		g_vecObj[i]->finaltick();
	}

}

void Render()
{
	float ClearColor[4] = { 0.3f, 0.3f, 0.3f, 1.f };
	CDevice::GetInst()->ClearRenderTarget(ClearColor);

	for (size_t i = 0; i < g_vecObj.size(); ++i)
	{
		g_vecObj[i]->render();
	}
	

	CDevice::GetInst()->Present();

}

void TestProgress()
{
	Tick();
	Render();
}

void TestRelease()
{
	Delete_Vec(g_vecObj);
}
