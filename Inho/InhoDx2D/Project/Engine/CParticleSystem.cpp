#include "pch.h"
#include "CParticleSystem.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

#include "CAssetMgr.h"
#include "CMesh.h"
#include "CMaterial.h"
#include "CTransform.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_MaxParticleCount(100)
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"ParticleMtrl"));

	Vec2 vResol = CDevice::GetInst()->GetRenderResolution();

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticleCount, SB_TYPE::READ_WRITE, true);

	m_CSParticleUpdate = (CParticleUpdate*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"ParticleUpdateShader").Get();

}

CParticleSystem::~CParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
		delete m_ParticleBuffer;
}

void CParticleSystem::finaltick()
{
	m_CSParticleUpdate->Execute();
}

void CParticleSystem::render()
{
	Transform()->UpdateData();

	m_ParticleBuffer->UpdateData(20);

	GetMaterial()->SetScalarParam(INT_0, 0);
	GetMaterial()->UpdateData();
	GetMesh()->render_asparticle(20);

	m_ParticleBuffer->Clear(20);
}

void CParticleSystem::UpdateData()
{
}
