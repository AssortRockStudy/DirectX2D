#include "pch.h"
#include "CPlayerScript.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "CAssetMgr.h"
#include "CMissileScript.h"
#include "CAnimator2D.h"

CPlayerScript::CPlayerScript()
	: m_Speed(100.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::begin()
{
	Ptr<CTexture> pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"LinkAnimAtlas", L"texture\\link.png");
	Animator2D()->Create(L"IDLE_UP", pAltasTex, Vec2(0.f, 260.f), Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(200.f, 200.f), 1, 10);
	Animator2D()->Create(L"IDLE_DOWN", pAltasTex, Vec2(0.f, 0.f), Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(200.f, 200.f), 3, 10);
	Animator2D()->Create(L"IDLE_LEFT", pAltasTex, Vec2(0.f, 130.f), Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(200.f, 200.f), 3, 10);
	Animator2D()->Create(L"IDLE_RIGHT", pAltasTex, Vec2(0.f, 390.f), Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(200.f, 200.f), 3, 10);

	Animator2D()->Create(L"MOVE_UP", pAltasTex, Vec2(0.f, 780.f), Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(200.f, 200.f), 10, 20);
	Animator2D()->Create(L"MOVE_DOWN", pAltasTex, Vec2(0.f, 520.f), Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(200.f, 200.f), 10, 20);
	Animator2D()->Create(L"MOVE_LEFT", pAltasTex, Vec2(0.f, 650.f), Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(200.f, 200.f), 10, 20);
	Animator2D()->Create(L"MOVE_RIGHT", pAltasTex, Vec2(0.f, 910.f), Vec2(0.f, 0.f), Vec2(120.f, 130.f), Vec2(200.f, 200.f), 10, 20);

	Animator2D()->Play(L"IDLE_DOWN");
}

void CPlayerScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (KEY_PRESSED(KEY::A))
		vPos.x -= DT * m_Speed;
	if (KEY_TAP(KEY::A))
		Animator2D()->Play(L"MOVE_LEFT");
	if (KEY_RELEASED(KEY::A))
		Animator2D()->Play(L"IDLE_LEFT");

	if (KEY_PRESSED(KEY::D))
		vPos.x += DT * m_Speed;
	if (KEY_TAP(KEY::D))
		Animator2D()->Play(L"MOVE_RIGHT");
	if (KEY_RELEASED(KEY::D))
		Animator2D()->Play(L"IDLE_RIGHT");

	if (KEY_PRESSED(KEY::W))
		vPos.y += DT * m_Speed;
	if (KEY_TAP(KEY::W))
		Animator2D()->Play(L"MOVE_UP");
	if (KEY_RELEASED(KEY::W))
		Animator2D()->Play(L"IDLE_UP");

	if (KEY_PRESSED(KEY::S))
		vPos.y -= DT * m_Speed;
	if (KEY_TAP(KEY::S))
		Animator2D()->Play(L"MOVE_DOWN");
	if (KEY_RELEASED(KEY::S))
		Animator2D()->Play(L"IDLE_DOWN");

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
		GetOwner()->Destroy();

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
