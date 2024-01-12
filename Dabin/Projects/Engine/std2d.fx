#ifndef _STD2D
#define _STD2D

#include "value.fx"

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
    //output.vPosition = float4(vFinalPos, 0.f, 1.f);
    
    // model coord -> * world * view * proj
    /*
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld); // 1로 확장: 이동 적용
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);
    */
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    
    // alpha blending (magenta background delete)
    if(g_btex_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f); // saturate: 0~1 넘지 않게 보정

        if (fAlpha<0.1f)
        {
            // 픽셀 쉐이더 중간에 폐기
            // clip(-1);
            discard;
        }
    }
    
    return vColor;
}

#endif
