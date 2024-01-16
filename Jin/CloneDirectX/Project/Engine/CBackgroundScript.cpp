#include "pch.h"
#include "CBackgroundScript.h"

void CBackgroundScript::tick()
{
}

CBackgroundScript::CBackgroundScript()
{
}

CBackgroundScript::~CBackgroundScript()
{
	static int i = 0;
	if (KEY_TAP(KEY::T))
	{
		i ? MeshRender()->GetMaterial()->SetScalarParam(INT_0, 1) : MeshRender()->GetMaterial()->SetScalarParam(INT_0, 0);
		i = !i;
	}
}
