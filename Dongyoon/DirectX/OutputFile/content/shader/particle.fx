#ifndef _PARTICLE
#define _PARTICLe

#include "value.fx"
#include "struct.fx"

StructuredBuffer<tParticle> g_ParticleBuffer : register(t20);

#define Particle g_ParticleBuffer[_in.iInstID]

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    uint iInstID : SV_InstanceID;
    
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    float InstID : FOG;
   
};

VS_OUT VS_Particle(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    g_ParticleBuffer[g_int_0].vWorldPos;
    
    float3 vWorldPos = (_in.vPos * Particle.vWorldScale.xyz) + Particle.vWorldPos.xyz;
    
    output.vPosition = mul(mul(float4(vWorldPos, 1.f), g_matView), g_matProj);
    output.vUV = _in.vUV;
    output.InstID = _in.iInstID;
    
    return output;

}

float4 PS_Particle(VS_OUT _in) : SV_Target
{
    if (!g_ParticleBuffer[(uint)_in.InstID].Active)
    {
        discard;
    }
    
    float4 vOutColor = g_ParticleBuffer[(uint) _in.InstID].vColor;
    
    if(g_btex_0)
    {
        vOutColor *= g_tex_0.Sample(g_sam_0, _in.vUV);
    }
    
    return vOutColor;
}

#endif