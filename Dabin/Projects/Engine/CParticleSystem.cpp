#include "pch.h"
#include "CParticleSystem.h"
#include "CAssetMgr.h"
#include "CDevice.h"
#include "CTransform.h"
#include "CParticleUpdate.h"
#include "CTimeMgr.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleCountMax(100)
	, m_ParticleBuffer(nullptr)
	, m_SpawnAccTime(0.f)
{
	// 전용 mesh & material 사용
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"ParticleMat"));

	// 임시 paritcle system 생성
	Vec2 vResol = CDevice::GetInst()->GetRenderResolution();
	FParticle arrParticle[100] = {};
	for (UINT i = 0; i < m_ParticleCountMax; ++i)
	{
		arrParticle[i].vWorldPos = Vec3(vResol.x / (m_ParticleCountMax + 1) * (i + 1) - (vResol.x / 2.f), 0.f, 99.f);
		arrParticle[i].vWorldScale = Vec3(50.f, 50.f, 1.f);
		arrParticle[i].Active = 0;
	}

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(FParticle), m_ParticleCountMax, SB_TYPE::READ_WRITE, true, arrParticle);	// 확인용으로 READ_WRITE (CPU 읽기 허용)
	
	m_ParticleModuleBuffer = new CStructuredBuffer;
	m_ParticleModuleBuffer->Create(sizeof(FParticleModule), 1, SB_TYPE::READ_ONLY, true);

	m_SpawnCountBuffer = new CStructuredBuffer;
	m_SpawnCountBuffer->Create(sizeof(FSpawnCount), 1, SB_TYPE::READ_WRITE, true);

	// compute shader for particle update
	m_CSParticleUpdate = (CParticleUpdate*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"ParticleUpdateShader").Get();

	// -------------------------
	// Module Setting
	// -------------------------
	// Spawn
	m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN] = 1;

	m_Module.vSpawnColor = Vec4(1.f, 0.f, 0.f, 1.f);
	m_Module.vSpawnScaleMin = Vec4(20.f, 20.f, 1.f, 1.f);
	m_Module.vSpawnScaleMax = Vec4(50.f, 20.f, 1.f, 1.f);

	m_Module.LifeMin = 5.f;
	m_Module.LifeMax = 5.f;
	m_Module.SpawnRate = 10;
	m_Module.SpaceType = 1;

	m_Module.SpawnShape = 0;
	m_Module.Radius = 100.f;
}

CParticleSystem::~CParticleSystem()
{
	if (m_ParticleBuffer)
		delete m_ParticleBuffer;

	if (m_ParticleModuleBuffer)
		delete m_ParticleModuleBuffer;

	if (m_SpawnCountBuffer)
		delete m_SpawnCountBuffer;
}

void CParticleSystem::UpdatePipeline()
{
}

void CParticleSystem::finaltick()
{
	// ----------------------
	// Set Module
	// ----------------------
	// Module: Spawn
	m_SpawnAccTime += DT;

	if (m_SpawnAccTime > 1.f / m_Module.SpawnRate)
	{
		// 누적 처리
		// - frame이 떨어지면 : DT를 누적시켰다가 한번에 처리해야 함
		float fSpawnCount = m_SpawnAccTime / (1.f / m_Module.SpawnRate);
		m_SpawnAccTime -= (1.f / (float)m_Module.SpawnRate) * floor(fSpawnCount);
		
		FSpawnCount count = FSpawnCount{ (int)fSpawnCount,0,};
		m_SpawnCountBuffer->SetData(&count);
	}
	else
	{
		FSpawnCount count = FSpawnCount{ 0, };
		m_SpawnCountBuffer->SetData(&count);
	}

	// Update Module
	m_ParticleModuleBuffer->SetData(&m_Module);
	m_ParticleModuleBuffer->UpdateCS_SRV(20);

	// ----------------------
	// Cacluate
	// ----------------------
	m_CSParticleUpdate->SetParticleBuffer(m_ParticleBuffer);
	m_CSParticleUpdate->SetParticleModuleBuffer(m_ParticleModuleBuffer);
	m_CSParticleUpdate->SetParticleSpawnCount(m_SpawnCountBuffer);

	m_CSParticleUpdate->Execute();

	//FParticle arrParticle[100] = {};
	//m_ParticleBuffer->GetData(arrParticle);
}

void CParticleSystem::render()
{
	// view, projection 행렬 전달
	Transform()->UpdatePipeline();

	// 1. binding
	m_ParticleBuffer->UpdatePipeline(20);

	// 2. rendering
	GetMaterial()->UpdatePipeline();
	GetMesh()->renderInstanced(m_ParticleCountMax);

	// pipeline binding clear
	m_ParticleBuffer->Clear(20);
}