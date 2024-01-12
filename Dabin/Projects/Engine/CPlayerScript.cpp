#include "pch.h"
#include "CPlayerScript.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "CAssetMgr.h"
#include "CMissileScript.h"

CPlayerScript::CPlayerScript()
	: m_Speed(100.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y += DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= DT * m_Speed;
	}

	if (KEY_PRESSED(KEY::X))
	{
		vRot.x += DT * XM_PI;
	}

	if (KEY_PRESSED(KEY::Y))
	{
		vRot.y += DT * XM_PI;
	}
	
	if (KEY_PRESSED(KEY::Z))
	{
		vRot.z += DT * XM_PI;
	}

	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeRotation(vRot);

	// GameObject »ý¼º
	if (KEY_TAP(KEY::SPACE))
	{
		vector<CGameObject*> vecChild = GetOwner()->GetChild();
		for (size_t i = 0; i < vecChild.size(); ++i)
			GamePlayStatic::DestroyGameObject(vecChild[i]);
		Destroy();

		/*
		CGameObject* pObj = nullptr;

		pObj = new CGameObject;
		pObj->SetName(L"Missile");
		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CMissileScript);

		pObj->Transform()->SetRelativePos(Transform()->GetRelativePos());
		pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));
		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicsShader>(L"Std2DShader"));

		GamePlayStatic::SpawnGameObject(pObj, 0);
		*/
	}
}