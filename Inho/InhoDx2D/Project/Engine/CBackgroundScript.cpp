#include "pch.h"
#include "CBackgroundScript.h"

#include "CKeyMgr.h"

CBackgroundScript::CBackgroundScript()
{
}

CBackgroundScript::~CBackgroundScript()
{
}

void CBackgroundScript::tick()
{
	static int i = 0;
	if (KEY_TAP(KEY::T)) {
		i == 0 ? i = 1 : i = 0;
		MeshRender()->GetMaterial()->SetScalarParam(INT_0, i);

	}
}
