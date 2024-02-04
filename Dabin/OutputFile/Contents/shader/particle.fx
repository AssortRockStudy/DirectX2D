#ifndef _PARTICLE
#define _PARTICLE

#include "value.fx"
#include "struct.fx"

StructuredBuffer<FParticle> g_ParticleBuffer : register(t20);
#define Particle g_ParticleBuffer[_in.InstID]

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    uint InstID : SV_InstanceID;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    uint InstID : FOG;
};

VS_OUT VS_Particle(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    float3 vWorldPos = (_in.vPos * Particle.vWorldScale.xyz) + Particle.vWorldPos.xyz;
    output.vPosition = mul(mul(float4(vWorldPos, 1.f), g_matView), g_matProj);
    output.vUV = _in.vUV;
    output.InstID = _in.InstID;
    
    return output;
}

// Gemotery Shader:
// 1. 비활성화 파티클 연산 중단
// 2. 빌보드 쉽게 구현

float4 PS_Particle(VS_OUT _in) : SV_Target
{
    if (!g_ParticleBuffer[_in.InstID].Active)
        discard;
    
    return float4(1.f, 0.f, 0.f, 1.f);
}

#endif