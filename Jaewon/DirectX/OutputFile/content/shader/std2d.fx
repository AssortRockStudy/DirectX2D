#ifndef _STD2D
#define _STD2D
#include "value.fx"

struct VS_IN
{
    float4 vColor : COLOR;
    float3 vPos : POSITION;
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
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    if (g_UseAnim2D){
        float2 vUV = g_vLeftTop + (g_vSlizeSize * _in.vUV);
        vColor = g_anim2d_tex.Sample(g_sam_1, vUV);
    }
    else{
        if (g_btex_0){
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
            float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);
            if (fAlpha < 0.1f)
                discard;
        }
    }
    
    return vColor;
}

#endif
