#pragma once
#include "CRenderComponent.h"
#include "CUpdateParticle.h"
// =======================================
// CParticleSystem: Particle Group�� ����, �����ϴ� Component
// =======================================
// - ParticleSystem�� ������ Particles�� �̷���� �����Ƿ� CPU�� �ƴ� GPU���� �����ؾ� ��
// - ���� CompouteShader ���

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    Ptr<CUpdateParticle>    m_CSParticleUpdate;
    
    CStructuredBuffer*      m_ParticleBuffer;
    UINT                    m_ParticleCountMax;

    FParticleModule         m_Module;
    CStructuredBuffer*      m_ParticleModuleBuffer;

    // Module: Spawn
    CStructuredBuffer*      m_SpawnCountBuffer;
    float                   m_SpawnAccTime;

public:
    virtual void UpdatePipeline() override;
    virtual void finaltick() override;
    virtual void render() override;

public:
    CParticleSystem();
    ~CParticleSystem();
};

