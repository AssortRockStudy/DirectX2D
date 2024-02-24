#ifndef _PARTICLE
#define _PARTICLE

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
    float3 vPos: POSITION;
    float2 vUV : TEXCOORD;
    uint  InstID : FOG;
};

VS_OUT VS_Particle(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPos = _in.vPos;
    output.vUV = _in.vUV;
    output.InstID = _in.iInstID;
    
    return output;
}

struct GS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    float InstID : FOG;
};

[maxvertexcount(6)]
void GS_Particle(point VS_OUT _in[1], inout TriangleStream<GS_OUT> _OutStream)
{
    GS_OUT output[4] = { (GS_OUT) 0.f, (GS_OUT) 0.f, (GS_OUT) 0.f, (GS_OUT) 0.f };
    
    tParticle particle = g_ParticleBuffer[(int) _in[0].InstID];
    if (0 == particle.Active)
        return;
    
    float3 vWorldPos = particle.vWorldPos.xyz;
    float4 vViewPos = mul(float4(vWorldPos, 1.f), g_matView);
    
    output[0].vPosition = vViewPos + float4((particle.vWorldScale.x * -0.5f), (particle.vWorldScale.y * 0.5f), 0.f, 0.f);
    output[1].vPosition = vViewPos + float4((particle.vWorldScale.x * 0.5f), (particle.vWorldScale.y * 0.5f), 0.f, 0.f);
    output[2].vPosition = vViewPos + float4((particle.vWorldScale.x * 0.5f), (particle.vWorldScale.y * -0.5f), 0.f, 0.f);
    output[3].vPosition = vViewPos + float4((particle.vWorldScale.x * -0.5f), (particle.vWorldScale.y * -0.5f), 0.f, 0.f);
    
    output[0].vPosition = mul(output[0].vPosition, g_matProj);
    output[1].vPosition = mul(output[1].vPosition, g_matProj);
    output[2].vPosition = mul(output[2].vPosition, g_matProj);
    output[3].vPosition = mul(output[3].vPosition, g_matProj);
    
    output[0].vUV = float2(0.f, 0.f);
    output[1].vUV = float2(1.f, 0.f);
    output[2].vUV = float2(1.f, 1.f);
    output[3].vUV = float2(0.f, 1.f);
    
    _OutStream.Append(output[0]);
    _OutStream.Append(output[2]);
    _OutStream.Append(output[3]);
    _OutStream.RestartStrip();
    
    _OutStream.Append(output[0]);
    _OutStream.Append(output[1]);
    _OutStream.Append(output[2]);
    _OutStream.RestartStrip();

}

float4 PS_Particle(VS_OUT _in) : SV_Target
{
    if (!g_ParticleBuffer[(uint) _in.InstID].Active)
    {
        discard;
    }
    float4 vOutColor = g_ParticleBuffer[(uint) _in.InstID].vColor;
    
    if (g_btex_0)
    {
        vOutColor *= g_tex_0.Sample(g_sam_0, _in.vUV);
    }
    
    return vOutColor;
}
#endif