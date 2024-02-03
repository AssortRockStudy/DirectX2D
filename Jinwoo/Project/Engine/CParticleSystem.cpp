#include "pch.h"
#include "CParticleSystem.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

#include "CTimeMgr.h"
#include "CAssetMgr.h"
#include "CMesh.h"
#include "CMaterial.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_MaxParticleCount(2000)
{
	// 전용 메쉬와 전용 머테리얼 사용
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"PointMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"ParticleMtrl"));

	// 해상도
	Vec2 vResol = CDevice::GetInst()->GetRenderResolution();

	// 파티클을 저장하는 구조화 버퍼
	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticleCount, SB_TYPE::READ_WRITE, true);

	// 파티클 모듈 정보를 저장하는 구조화 버퍼
	m_ParticleModuleBuffer = new CStructuredBuffer;
	UINT ModuleAddSize = 0;
	if (sizeof(tParticleModule) % 16 != 0)
	{
		ModuleAddSize = 16 - (sizeof(tParticleModule) % 16);
	}

	m_ParticleModuleBuffer->Create(sizeof(tParticleModule) + ModuleAddSize , 1, SB_TYPE::READ_ONLY, true);

	// 파티클 업데이트용 컴퓨트 셰이더 참조
	m_CSParticleUpdate = (CParticleUpdate*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"ParticleUpdateShader").Get();

	// SpawnCount를 전달할 구조화 버퍼
	m_SpawnCountBuffer = new CStructuredBuffer;
	m_SpawnCountBuffer->Create(sizeof(tSpawnCount), 1, SB_TYPE::READ_WRITE, true);

	// 파티클 모듈값 세팅
	m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN] = 1;

	m_Module.SpaceType = 1;
	m_Module.vSpawnColor = Vec4(0.2f, 0.5f, 0.8f, 1.f);
	m_Module.vSpawnMinScale = Vec4(20.f, 20.f, 1.f, 1.f);
	m_Module.vSpawnMaxScale = Vec4(20.f, 20.f, 1.f, 1.f);
	m_Module.MinMass = 1.f;
	m_Module.MaxMass = 1.f;
	m_Module.MinLife = 1.f;
	m_Module.MaxLife = 3.f;
	m_Module.SpawnShape = 1;
	m_Module.Radius = 100.f;
	m_Module.vSpawnBoxScale = Vec4(300.f, 300.f, 0.f, 0.f);
	m_Module.SpawnRate = 50;

	// Add Velocity
	m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = 1;
	m_Module.AddVelocityType = 0;
	m_Module.MinSpeed = 10.f;
	m_Module.MaxSpeed = 20.f;

	// Scale
	m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::SCALE] = 0;
	m_Module.vScaleRatio = Vec3(0.1f, 0.1f, 0.1f);

	// Noise Force
	m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = 1;
	m_Module.NoiseForceScale = 10.f;
	m_Module.NoiseForceTerm = 0.3f;

	// Calculate Force
	m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::CALCULATE_FORCE] = 1;

	// Render 
	m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = 1;
	m_Module.VelocityAlignment = 1; // 속도에 따른 방향 정렬
	m_Module.AlphaBasedLife = 1;
	m_Module.AlphaMaxAge = 2.f;

	m_ParticleTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\AlphaCircle.png", L"texture\\particle\\AlphaCircle.png");
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

	if ((1.f / m_Module.SpawnRate) < m_Time)
	{
		// 누적 시간을 스폰 간격으로 나눈 값
		float fSpawnCount = m_Time / (1.f / m_Module.SpawnRate);

		// 스폰 간격을 제외한 잔량을 남은 누적시간으로 설정
		m_Time -= (1.f / m_Module.SpawnRate) * floorf(fSpawnCount);

		tSpawnCount count = tSpawnCount{ (int)fSpawnCount ,0,0,0};
		m_SpawnCountBuffer->SetData(&count);
	}
	else
	{
		tSpawnCount count = tSpawnCount{ 0,0,0,0};
		m_SpawnCountBuffer->SetData(&count);
	}

	// 파티클 모듈정보 업데이트
	m_ParticleModuleBuffer->SetData(&m_Module);
	m_ParticleModuleBuffer->UpdateData_CS_SRV(40);

	// 파티컬 업데이트
	// 어떤 버퍼를 업데이트할지 설정
	m_CSParticleUpdate->SetParticleBuffer(m_ParticleBuffer);
	m_CSParticleUpdate->SetParticleModuleBuffer(m_ParticleModuleBuffer);
	m_CSParticleUpdate->SetParticleSpawnCount(m_SpawnCountBuffer);
	m_CSParticleUpdate->SetParticleWorldPos(Transform()->GetWorldPos());

	m_CSParticleUpdate->Execute();
}

void CParticleSystem::render()
{
	// View, Proj 행렬 전달
	Transform()->UpdateData();

	// ParticleBuffer 바인딩
	m_ParticleBuffer->UpdateData(30);
	m_ParticleModuleBuffer->UpdateData(31);

	// 파티클 개별 렌더링 -> 인스턴싱
	GetMaterial()->SetScalarParam(INT_0, 0);
	GetMaterial()->SetTexParam(TEX_0, m_ParticleTex);
	GetMaterial()->UpdateData();

	GetMesh()->render_asparticle(m_MaxParticleCount);

	// 렌더링 때 사용한 리소스 바인딩 클리어
	m_ParticleBuffer->Clear(30);
	m_ParticleModuleBuffer->Clear(31);
}


void CParticleSystem::UpdateData()
{
}