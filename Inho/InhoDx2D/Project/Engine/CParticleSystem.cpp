#include "pch.h"
#include "CParticleSystem.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

#include "CAssetMgr.h"
#include "CMesh.h"
#include "CMaterial.h"
#include "CTransform.h"
#include "CRenderMgr.h"
#include "CTimeMgr.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_MaxParticleCount(2000)
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

	m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN] = 1;

	m_Module.SpawnModule.SpaceType = 1;
	m_Module.SpawnModule.vSpawnColor = Vec4(0.2f, 0.4f, 0.9f, 1.f);
	m_Module.SpawnModule.vSpawnMinScale = Vec4(50.f, 50.f, 1.f, 1.f);
	m_Module.SpawnModule.vSpawnMaxScale = Vec4(200.f, 200.f, 1.f, 1.f);
	m_Module.SpawnModule.MinLife = 0.4f;
	m_Module.SpawnModule.MaxLife = 1.f;
	m_Module.SpawnModule.SpawnShape = 1;
	m_Module.SpawnModule.Radius = 100.f;
	m_Module.SpawnModule.SpawnRate = 100;
	m_Module.SpawnModule.vSpawnBoxScale = Vec4(500.f, 500.f, 0.f, 0.f);

	m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = 1;
	m_Module.VelocityModule.AddVelocityType = 0;
	m_Module.VelocityModule.MinSpeed = 100;
	m_Module.VelocityModule.MaxSpeed = 200;
	m_Module.VelocityModule.FixedDirection;
	m_Module.VelocityModule.FixedAngle;

	m_ParticleTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\CartoonSmoke.png", L"texture\\particle\\CartoonSmoke.png");
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
	m_Time += DT;

	if ((1.f / m_Module.SpawnModule.SpawnRate) < m_Time) {
		float fSpawnCount = m_Time / (1.f / m_Module.SpawnModule.SpawnRate);
		m_Time -= (1.f / m_Module.SpawnModule.SpawnRate) * floorf(fSpawnCount);

		tSpawnCount count = tSpawnCount{ (int)fSpawnCount, 0, 0, 0 };
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
	m_CSParticleUpdate->SetParticleWorldPos(Transform()->GetWorldPos());

	m_CSParticleUpdate->Execute();

	if (CRenderMgr::GetInst()->IsDebugPosition()) {
		GamePlayStatic::DrawDebugCross(Transform()->GetWorldPos(), 20.f, Vec3(0.f, 1.f, 0.f), true);
	}
}

void CParticleSystem::render()
{
	Transform()->UpdateData();

	m_ParticleBuffer->UpdateData(20);

	GetMaterial()->SetScalarParam(INT_0, 0);
	GetMaterial()->SetTexParam(TEX_0, m_ParticleTex);
	GetMaterial()->UpdateData();
	GetMesh()->render_asparticle(m_MaxParticleCount);

	m_ParticleBuffer->Clear(20);
}

void CParticleSystem::UpdateData()
{
}
