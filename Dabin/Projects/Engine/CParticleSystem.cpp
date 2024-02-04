#include "pch.h"
#include "CParticleSystem.h"
#include "CAssetMgr.h"
#include "CDevice.h"
#include "CTransform.h"
#include "CUpdateParticle.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_MaxParticleCount(100)
	, m_ParticleBuffer(nullptr)
{
	// ���� mesh & material ���
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"ParticleMat"));

	// �ӽ� paritcle system ����
	Vec2 vResol = CDevice::GetInst()->GetRenderResolution();
	FParticle arrParticle[100] = {};
	for (int i = 0; i < m_MaxParticleCount; ++i)
	{
		arrParticle[i].vWorldPos = Vec3(vResol.x / (m_MaxParticleCount + 1) * (i + 1) - (vResol.x / 2.f), 0.f, 99.f);
		arrParticle[i].vWorldScale = Vec3(50.f, 50.f, 1.f);
		arrParticle[i].Active = 1;
	}

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(FParticle), m_MaxParticleCount, SB_TYPE::READ_WRITE, true, arrParticle);	// Ȯ�ο����� READ_WRITE (CPU �б� ���)
	
	// compute shader for particle update
	m_CSParticleUpdate = (CUpdateParticle*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"UpdateParticleShader").Get();
}

CParticleSystem::~CParticleSystem()
{
	if (m_ParticleBuffer)
		delete m_ParticleBuffer;
}

void CParticleSystem::UpdatePipeline()
{
}

void CParticleSystem::finaltick()
{
	m_CSParticleUpdate->SetParticleBuffer(m_ParticleBuffer);
	m_CSParticleUpdate->Execute();

	//FParticle arrParticle[100] = {};
	//m_ParticleBuffer->GetData(arrParticle);
}

void CParticleSystem::render()
{
	// view, projection ��� ����
	Transform()->UpdatePipeline();

	// 1. binding
	m_ParticleBuffer->UpdatePipeline(20);

	// 2. rendering
	GetMaterial()->UpdatePipeline();
	GetMesh()->renderInstanced(m_MaxParticleCount);

	// pipeline binding clear
	m_ParticleBuffer->Clear(20);
}