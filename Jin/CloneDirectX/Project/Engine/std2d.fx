#ifndef _STD2D
#define _STD2D

#include "value.fx"

StructuredBuffer<float4> g_Data : register(t14);


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
    
    float3 vWorldPos : POSITION;
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
    output.vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    
    if (g_UseAnim2D)
    {
        float2 vBackgroundLeftTop = g_vLeftTop + (g_vSlizeSize / 2.f) - (g_vBackground / 2.f);
        vBackgroundLeftTop -= g_vOffset;
        float2 vUV = vBackgroundLeftTop + (g_vBackground * _in.vUV);
        
        if (vUV.x < g_vLeftTop.x || (g_vLeftTop.x + g_vSlizeSize.x) < vUV.x
            || vUV.y < g_vLeftTop.y || (g_vLeftTop.y + g_vSlizeSize.y) < vUV.y)
        {
            //vColor = float4(1.f, 1.f, 0.f, 1.f);
            discard;
        }
        else
        {
            vColor = g_anim2d_tex.Sample(g_sam_1, vUV);
        }
    }
    else
    {
        if (g_btex_0)
        {

            //vColor = g_tex_0.Sample(g_sam_1, _in.vUV + float2(g_time * 0.1, 0.f));
            vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        
            float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);
        
            if (fAlpha < 0.1f)
                discard;
        }
    }
    
    if ( 0 == g_Light2D[0].LightType) // Directional
    {
        vColor.rgb *= g_Light2D[0].vAmbient;
    }
    else if ( 1 == g_Light2D[0].LightType) // Point
    {
        float fDist = distance(g_Light2D[0].vWorldPos, _in.vWorldPos);
        if (fDist < g_Light2D[0].fRadius)
        {
            vColor.rgb *= g_Light2D[0].vColor;
        }
        else
        {
            vColor.rgb *= 0.f;
        }

    }
    else // Spot light
    {}
    
    g_Light2D[0].vWorldPos;
    return vColor;
}

#endif
