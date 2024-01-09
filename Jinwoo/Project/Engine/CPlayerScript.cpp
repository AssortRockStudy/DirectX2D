#include "pch.h"
#include "CPlayerScript.h"

#include "CAssetMgr.h"
#include "CGameObject.h"
#include "CMissileScript.h"

CPlayerScript::CPlayerScript()
	: m_Speed(300.f)
{

}

CPlayerScript::~CPlayerScript()
{
}



void CPlayerScript::begin()
{
	Ptr<CTexture> pAtlasTex = CAssetMgr::GetInst()->Load<CTexture>(L"AnimAtlasTex", L"texture\\link.png");
	Animator2D()->Create(L"IDLE_UP", pAtlasTex, Vec2(0.f, 260.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(150.f, 150.f), 1, 5.f);
	Animator2D()->Create(L"IDLE_DOWN", pAtlasTex, Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(150.f, 150.f), 3, 5.f);
	Animator2D()->Create(L"IDLE_LEFT", pAtlasTex, Vec2(0.f, 130.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(150.f, 150.f), 3, 5.f);
	Animator2D()->Create(L"IDLE_RIGHT", pAtlasTex, Vec2(0.f, 390.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(150.f, 150.f), 3, 5.f);

	Animator2D()->Create(L"MOVE_UP", pAtlasTex, Vec2(0.f, 780.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(150.f, 150.f), 10, 20.f);
	Animator2D()->Create(L"MOVE_DOWN", pAtlasTex, Vec2(0.f, 520.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(150.f, 150.f), 10, 20.f);
	Animator2D()->Create(L"MOVE_LEFT", pAtlasTex, Vec2(0.f, 650.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(150.f, 150.f), 10, 20.f);
	Animator2D()->Create(L"MOVE_RIGHT", pAtlasTex, Vec2(0.f, 910.f), Vec2(120.f, 130.f), Vec2(0.f, 0.f), Vec2(150.f, 150.f), 10, 20.f);
}

void CPlayerScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (KEY_PRESSED(UP))
	{
		vPos.y += DT * m_Speed;
	}
	if (KEY_TAP(UP))
	{
		Animator2D()->Play(L"MOVE_UP");
	}
	if (KEY_RELEASED(UP))
	{
		Animator2D()->Play(L"IDLE_UP");
	}


	if (KEY_PRESSED(DOWN))
	{
		vPos.y -= DT * m_Speed;
	}
	if (KEY_TAP(DOWN))
	{
		Animator2D()->Play(L"MOVE_DOWN");
	}
	if (KEY_RELEASED(DOWN))
	{
		Animator2D()->Play(L"IDLE_DOWN");
	}


	if (KEY_PRESSED(LEFT))
	{
		vPos.x -= DT * m_Speed;
	}
	if (KEY_TAP(LEFT))
	{
		Animator2D()->Play(L"MOVE_LEFT");
	}
	if (KEY_RELEASED(LEFT))
	{
		Animator2D()->Play(L"IDLE_LEFT");
	}


	if (KEY_PRESSED(RIGHT))
	{
		vPos.x += DT * m_Speed;
	}
	if (KEY_TAP(RIGHT))
	{
		Animator2D()->Play(L"MOVE_RIGHT");
	}
	if (KEY_RELEASED(RIGHT))
	{
		Animator2D()->Play(L"IDLE_RIGHT");
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
		GetOwner()->Destroy();

		CGameObject* pObj = nullptr;

		pObj = new CGameObject;
		pObj->SetName(L"Missile");
		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CMissileScript);

		pObj->Transform()->SetRelativePos(Transform()->GetRelativePos());
		pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		GamePlayStatic::SpawnGameObject(pObj, 0);
	}

	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeRotation(vRot);
}

void CPlayerScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	_OtherObj->Destroy();
}

void CPlayerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
