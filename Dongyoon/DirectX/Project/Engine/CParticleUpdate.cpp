#include "pch.h"
#include "CParticleUpdate.h"


CParticleUpdate::CParticleUpdate()
	: CComputeShader(32, 1, 1)
{
	Create(L"shader\\particle_update.fx", "CS_ParticleUpdate");
}

CParticleUpdate::~CParticleUpdate()
{
}

int CParticleUpdate::UpdateData()
{
	if (m_ParticleBuffer == nullptr)
		return E_FAIL;

	m_Const.iArr[0] = m_ParticleBuffer->GetElementCount();
	
	m_ParticleBuffer->UpdateData_CS_UAV(0);
	m_SpawnCountBuffer->UpdateData_CS_UAV(1);

	m_ParticleModuleBuffer->UpdateData_CS_SRV(20);

	return S_OK;
}

void CParticleUpdate::UpdateGroupCount()
{
	UINT GroupX = (m_ParticleBuffer->GetElementCount() / m_ThreadX);
	if (m_ParticleBuffer->GetElementCount() % m_ThreadX != 0)
		GroupX += 1;

	SetGroup(GroupX, 1, 1);
}

void CParticleUpdate::Clear()
{
	m_ParticleBuffer->Clear_CS_UAV();
	m_ParticleBuffer = nullptr;

	m_ParticleModuleBuffer->Clear_CS_SRV();
	m_ParticleModuleBuffer = nullptr;

	m_SpawnCountBuffer->Clear_CS_UAV();
	m_SpawnCountBuffer = nullptr;
}