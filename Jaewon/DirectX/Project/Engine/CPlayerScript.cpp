#include "pch.h"
#include "CPlayerScript.h"
#include "CAssetMgr.h"
#include "CMissileScript.h"
#include "CGameObject.h"

CPlayerScript::CPlayerScript()
	: m_Speed(500.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();

	if (KEY_PRESSED(KEY::UP))
		vPos.y += DT * m_Speed;

	if (KEY_PRESSED(KEY::DOWN))
		vPos.y -= DT * m_Speed;

	if (KEY_PRESSED(KEY::LEFT))
		vPos.x -= DT * m_Speed;

	if (KEY_PRESSED(KEY::RIGHT))
		vPos.x += DT * m_Speed;

	if (KEY_PRESSED(KEY::X))
		vRot.x += DT * XM_PI;

	if (KEY_PRESSED(KEY::Y))
		vRot.y += DT * XM_PI;

	if (KEY_PRESSED(KEY::Z))
		vRot.z += DT * XM_PI;

	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeRotation(vRot);

	if (KEY_TAP(KEY::SPACE))
	{
		GetOwner()->Destroy();
		// GameObject ����
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

	if (KEY_PRESSED(KEY::SPACE))
	{
		Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();
		if (nullptr != pMtrl)
			pMtrl->SetScalarParam(INT_0, 1);
	}
	else if (KEY_RELEASED(KEY::SPACE))
	{
		Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();
		if (nullptr != pMtrl)
			pMtrl->SetScalarParam(INT_0, 0);
	}
}

void CPlayerScript::BeginOverlap(CCollider2D* _Collider
	, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	_OtherObj->Destroy();
}

void CPlayerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}