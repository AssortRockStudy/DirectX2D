#include "pch.h"
#include "CUpdateParticle.h"

CUpdateParticle::CUpdateParticle()
	: CComputeShader(1024, 1, 1)
{
	Create(L"shader\\particle_update.fx", "CS_UpdateParticle");
}

CUpdateParticle::~CUpdateParticle()
{
}

int CUpdateParticle::UpdatePipeline()
{
	if (!m_ParticleBuffer)
		return E_FAIL;

	m_Const.iArr[0] = m_ParticleBuffer->GetElementCount();
	m_ParticleBuffer->UpdatedCS_UAV(0);

	return S_OK;
}

void CUpdateParticle::UpdateGroupCount()
{
	UINT GroupX = (m_ParticleBuffer->GetElementCount() / m_ThreadX);
	if (m_ParticleBuffer->GetElementCount() % m_ThreadX != 0)
		GroupX += 1;

	SetGroup(GroupX, 1, 1);
}

void CUpdateParticle::Clear()
{
	m_ParticleBuffer->ClearCS_UAV();
	m_ParticleBuffer = nullptr;
}
