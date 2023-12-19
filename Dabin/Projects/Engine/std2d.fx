#ifndef _STD2D
#define _STD2D

// constant buffer (~2^12 == 4096 크기제한)
cbuffer TRANSFORM : register(b0)
{
    row_major float4x4 g_matWorld;  // row_major type: 행렬 전치시켜 저장
}

struct VS_IN
{
    float3 vPos : POSITION; // Sementic
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
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
    
    //float2 vFinalPos = _in.vPos.xy * g_vWorldScale.xy + g_vWorldPos.xy;
    // output.vPosition = float4(vFinalPos, 0.f, 1.f);
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWorld);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    return _in.vColor;
}

#endif
