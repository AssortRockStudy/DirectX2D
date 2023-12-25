#ifndef _STD2D
#define _STD2D

cbuffer TRANSFORM : register(b0)
{
    row_major float4x4 g_matWorld;
}

struct VS_IN
{
    // Sementic
    float4 vColor : COLOR;
    float3 vPos : POSITION; // �ø�ƽ
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
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWorld);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    return _in.vColor;
    //return float4(1.f, 0.f, 0.f, 1.f);
}

#endif
