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
	, m_MaxParticleCount(100)
{
	// 전용 메쉬와 전용 재질 사용
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"ParticleMtrl"));

	//렌더링 해상도
	Vec2 vResol = CDevice::GetInst()->GetRenderResolution();

	// 임시로 5개의 파티클이 초기 데이터를 입력하면서 구조화 버퍼 생성
	tParticle arrParticle[1000] = {};

	for (int i = 0; i < m_MaxParticleCount; ++i)
	{
		arrParticle[i].vWorldPos = Vec3((vResol.x / -2.f) + (i + 1) * vResol.x / (m_MaxParticleCount + 1), 0.f, 200.f);
		arrParticle[i].vWorldScale = Vec3(10.f, 10.f, 1.f);
		arrParticle[i].Active = 1;
	}

	// 파티클을 저장하는 구조화 버퍼
	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticleCount, SB_TYPE::READ_WRITE, true, arrParticle);

	// 파티클 모듈정보를 저장하는 구조화버퍼
	m_ParticleModuleBuffer = new CStructuredBuffer;
	m_ParticleModuleBuffer->Create(sizeof(tParticleModule), 1, SB_TYPE::READ_ONLY, true);

	// 파티클 업데이트용 컴퓨트 쉐이더 참조
	m_CSParticleUpdate = (CParticleUpdate*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"ParticleUpdateShader").Get();

	// SpawnCount 전달용 구조화버퍼
	m_SpawnCountBuffer = new CStructuredBuffer;
	m_SpawnCountBuffer->Create(sizeof(tSpawnCount), 1, SB_TYPE::READ_WRITE, true);

	//초기 모듈 세팅
	m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN] = 1;

	m_Module.SpaceType = 1;
	m_Module.vSpawnColor = Vec4(1.f, 0.f, 0.f, 1.f);
	m_Module.vSpawnMinScale = Vec4(20.f, 20.f, 1.f, 1.f);
	m_Module.VSpawnMaxScale = Vec4(20.f, 20.f, 1.f, 1.f);
	m_Module.MinLife = 5.f;
	m_Module.MaxLife = 5.f;
	m_Module.SpawnShape = 0; // 0 : Sphere
	m_Module.Radius = 100.f;

	m_Module.SpawnRate = 100;

}

CParticleSystem::~CParticleSystem()
{
	if (m_ParticleBuffer != nullptr)
		delete m_ParticleBuffer;

	if (m_ParticleModuleBuffer != nullptr)
		delete m_ParticleModuleBuffer;

	if (m_SpawnCountBuffer != nullptr)
		delete m_SpawnCountBuffer;
}

void CParticleSystem::finaltick()
{

	m_Time += DT;

	if ((1.f / m_Module.SpawnRate) < m_Time)
	{
		// 누적 시간을 스폰 간격으로 나눈 값
		float fSpawnCount = m_Time / (1.f / m_Module.SpawnRate);

		// 스폰 간격을 제외한 잔량을 남은 누적시간으로 절성
		m_Time -= (1.f / m_Module.SpawnRate) * floorf(fSpawnCount);

		tSpawnCount count = tSpawnCount{ (int)fSpawnCount, 0, 0, 0 };
		m_SpawnCountBuffer->SetData(&count);
	}
	else
	{
		tSpawnCount count = tSpawnCount{ 0, 0, 0, 0 };
		m_SpawnCountBuffer->SetData(&count);
	}

	// 파티클 모듈정보 업데이트
	m_ParticleModuleBuffer->SetData(&m_Module);
	m_ParticleModuleBuffer->UpdateData_CS_SRV(20);

	// 파티컬 업데이트 컴퓨트 쉐이더
	m_CSParticleUpdate->SetParticleBuffer(m_ParticleBuffer);
	m_CSParticleUpdate->SetParticleModuleBuffer(m_ParticleModuleBuffer);
	m_CSParticleUpdate->SetParticleSpawnCount(m_SpawnCountBuffer);
	//m_CSParticleUpdate->SetParticleWorldPos();

	m_CSParticleUpdate->Execute();

	tParticle arrParticle[100] = {};
	m_ParticleBuffer->GetData(arrParticle);
}

void CParticleSystem::render()
{
	//View, Porj 행렬 전달
	Transform()->UpdateData();

	//ParticleBuffer 바인딩
	m_ParticleBuffer->UpdateData(20);

	// 파티클 개별 랜더링 -> 인스턴싱
	GetMaterial()->SetScalarParam(INT_0, 0);
	GetMaterial()->UpdateDate();
	GetMesh()->Render_As_Particle(m_MaxParticleCount);

	//렌더링 때 사용한 리소스 바인딩 clear
	m_ParticleBuffer->Clear(20);
}

void CParticleSystem::UpdateData()
{
}