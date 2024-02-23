#include "pch.h"
#include "CParticleSystem.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

#include "CAssetMgr.h"
#include "CMesh.h"
#include "CMaterial.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_MaxParticleCount(5)
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"ParticleMtrl"));

	Vec2 vResol = CDevice::GetInst()->GetRenderResolution();

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), 5, SB_TYPE::READ_WRITE, true);
}

CParticleSystem::~CParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
		delete m_ParticleBuffer;
}

void CParticleSystem::finaltick()
{
}

void CParticleSystem::render()
{
	Transform()->UpdateData();

	m_ParticleBuffer->UpdateData(20);

	for (int i = 0; i < m_MaxParticleCount; ++i) {
		GetMaterial()->SetScalarParam(INT_0, i);
		GetMaterial()->UpdateData();
		GetMesh()->render();
	}
}

void CParticleSystem::UpdateData()
{
}
