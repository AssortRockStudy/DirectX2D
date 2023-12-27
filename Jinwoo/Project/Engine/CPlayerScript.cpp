#include "pch.h"
#include "CPlayerScript.h"

#include "CAssetMgr.h"
#include "CMissileScript.h"

CPlayerScript::CPlayerScript()
	: m_Speed(300.f)
{
}

CPlayerScript::~CPlayerScript()
{
}



void CPlayerScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (KEY_PRESSED(UP))
	{
		vPos.y += DT * m_Speed;
	}

	if (KEY_PRESSED(DOWN))
	{
		vPos.y -= DT * m_Speed;
	}

	if (KEY_PRESSED(LEFT))
	{
		vPos.x -= DT * m_Speed;
	}

	if (KEY_PRESSED(RIGHT))
	{
		vPos.x += DT * m_Speed;
	}

	if (KEY_PRESSED(X))
	{
		vRot.x += DT * XM_PI;
	}

	if (KEY_PRESSED(Y))
	{
		vRot.y += DT * XM_PI;
	}

	if (KEY_PRESSED(Z))
	{
		vRot.z += DT * XM_PI;
	}

	if (KEY_TAP(SPACE))
	{
		Destroy();

		//CGameObject* pObj = nullptr;

		//pObj = new CGameObject;
		//pObj->SetName(L"Missile");
		//pObj->AddComponent(new CTransform);
		//pObj->AddComponent(new CMeshRender);
		//pObj->AddComponent(new CMissileScript);

		//pObj->Transform()->SetRelativePos(Transform()->GetRelativePos());
		//pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

		//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		//pObj->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicsShader>(L"EffectShader"));

		//GamePlayStatic::SpawnGameObject(pObj, 0);
	}

	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeRotation(vRot);
}
