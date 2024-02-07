#pragma once
#include "CRenderComponent.h"
#include "CUpdateParticle.h"
// =======================================
// CParticleSystem: Particle Group을 생성, 관리하는 Component
// =======================================
// - ParticleSystem은 수많은 Particles로 이루어져 있으므로 CPU가 아닌 GPU에서 연산해야 함
// - 따라서 CompouteShader 사용

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

