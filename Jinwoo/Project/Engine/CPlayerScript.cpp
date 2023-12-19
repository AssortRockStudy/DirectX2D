#include "pch.h"
#include "CPlayerScript.h"


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

	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeRotation(vRot);
}
