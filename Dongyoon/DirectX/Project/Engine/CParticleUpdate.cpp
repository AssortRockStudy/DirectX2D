#include "pch.h"
#include "CParticleUpdate.h"


CParticleUpdate::CParticleUpdate()
	: CComputeShader(1024, 1, 1)
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
}