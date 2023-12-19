#include "pch.h"
#include "CPlayerScript.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTransform.h"

CPlayerScript::CPlayerScript()
	: m_Speed(2.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos();


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

	/*
	if (KEY_PRESSED(KEY::UP))
	{
		g_Transform.vWorldScale += DT * Vec4(1.f, 1.f, 1.f, 1.f);
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		g_Transform.vWorldScale -= DT * Vec4(1.f, 1.f, 1.f, 1.f);
	}
	*/

	Transform()->SetRelativePos(vPos);
}