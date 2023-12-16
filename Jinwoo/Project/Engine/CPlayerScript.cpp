#include "pch.h"
#include "CPlayerScript.h"


CPlayerScript::CPlayerScript()
	: m_Speed(0.1f)
{
}

CPlayerScript::~CPlayerScript()
{
}



void CPlayerScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(W))
	{
		vPos.y += DT * m_Speed;
	}

	if (KEY_PRESSED(S))
	{
		vPos.y -= DT * m_Speed;
	}

	if (KEY_PRESSED(A))
	{
		vPos.x -= DT * m_Speed;
	}

	if (KEY_PRESSED(D))
	{
		vPos.x += DT * m_Speed;
	}

	Transform()->SetRelativePos(vPos);
}
