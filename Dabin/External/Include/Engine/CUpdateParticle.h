#pragma once
#include "CComputeShader.h"
// =======================================
// CUpdateParticle: Particle Update Function
// =======================================

class CUpdateParticle :
    public CComputeShader
{
private:
    CStructuredBuffer* m_ParticleBuffer;

public:
    virtual int UpdatePipeline() override;
    virtual void UpdateGroupCount() override;
    virtual void Clear() override;

public:
    void SetParticleBuffer(CStructuredBuffer* _ParticleBuffer) { m_ParticleBuffer = _ParticleBuffer; }

public:
    CUpdateParticle();
    ~CUpdateParticle();
};

