#include "pch.h"
#include "CScript.h"

void CScript::Destroy()
{
	GamePlayStatic::DestroyGameObject(GetOwner());
}

CScript::CScript()
	: CComponent(COMPONENT_TYPE::SCRIPT)
{
}

CScript::~CScript()
{
}
