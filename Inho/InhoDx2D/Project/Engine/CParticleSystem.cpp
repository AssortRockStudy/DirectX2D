#include "pch.h"
#include "CParticleSystem.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

#include "CAssetMgr.h"
#include "CMesh.h"
#include "CMaterial.h"
#include "CTransform.h"

#include "CTimeMgr.h"

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

	m_ParticleModuleBuffer = new CStructuredBuffer;
	m_ParticleModuleBuffer->Create(sizeof(tParticleModule), 1, SB_TYPE::READ_ONLY, true);

	m_SpawnCountBuffer = new CStructuredBuffer;
	m_SpawnCountBuffer->Create(sizeof(tSpawnCount), 1, SB_TYPE::READ_WRITE, true);

	m_CSParticleUpdate = (CParticleUpdate*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"ParticleUpdateShader").Get();

}

CParticleSystem::~CParticleSystem()
{
	if (nullptr != m_ParticleBuffer)
		delete m_ParticleBuffer;

	if (nullptr != m_ParticleModuleBuffer)
		delete m_ParticleModuleBuffer;

	if (nullptr != m_SpawnCountBuffer)
		delete m_SpawnCountBuffer;
}

void CParticleSystem::finaltick()
{
	m_Module.SpawnModule.SpaceType = 1;
	m_Module.SpawnModule.vSpawnColor = Vec4(1.f, 0.f, 0.f, 1.f);
	m_Module.SpawnModule.vSpawnMinScale = Vec4(20.f, 20.f, 1.f, 1.f);
	m_Module.SpawnModule.vSpawnMaxScale = Vec4(20.f, 20.f, 1.f, 1.f);
	m_Module.SpawnModule.MinLife = 5.f;
	m_Module.SpawnModule.MaxLife = 5.f;
	m_Module.SpawnModule.SpawnRate = 100;

	m_Time += DT;

	if ((1.f / m_Module.SpawnModule.SpawnRate) < m_Time) {
		m_Time = 0.f;
		tSpawnCount count = tSpawnCount{ 1, };
		m_SpawnCountBuffer->SetData(&count);
	}
	else {
		tSpawnCount count = tSpawnCount{ 0, };
		m_SpawnCountBuffer->SetData(&count);
	}

	m_ParticleModuleBuffer->SetData(&m_Module);
	m_ParticleModuleBuffer->UpdateData_CS_SRV(20);

	m_CSParticleUpdate->SetParticleBuffer(m_ParticleBuffer);
	m_CSParticleUpdate->SetParticleModuleBuffer(m_ParticleModuleBuffer);
	m_CSParticleUpdate->SetParticleSpawnCount(m_SpawnCountBuffer);

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
