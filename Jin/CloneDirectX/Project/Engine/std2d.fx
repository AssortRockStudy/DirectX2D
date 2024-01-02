#ifndef _STD2D
#define _STD2D

cbuffer TRANSFORM : register(b0)
{
    row_major Matrix g_matWorld;
    row_major Matrix g_matWorldInv;

    row_major Matrix g_matView;
    row_major Matrix g_matViewInv;

    row_major Matrix g_matProj;
    row_major Matrix g_matProjInv;

    row_major Matrix g_matWV;
    row_major Matrix g_matWVP;
}

Texture2D g_tex_0 : register(t0);

SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);

struct VS_IN
{
    // Sementic
    float4 vColor : COLOR;
    float3 vPos : POSITION; // 시맨틱
    float2 vUV :    TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    
    //// 로컬(모델) 좌표를 -> 월드 -> 뷰 -> 투영 좌표계로 순차적으로 변환
    //float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    //float4 vViewPos = mul(vWorldPos, g_matView);
    //float4 vProjPos = mul(vViewPos, g_matProj);
            
    //output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    return vColor;
}

#endif
