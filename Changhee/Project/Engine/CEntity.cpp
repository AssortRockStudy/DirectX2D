#include "pch.h"
#include "CEntity.h"

UINT CEntity::g_NextID = 0;

CEntity::CEntity()
	: m_iID(g_NextID++)
{
}

CEntity::~CEntity()
{
}
