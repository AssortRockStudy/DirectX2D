#ifndef _STD2D
#define _STD2D

#include "value.fx"

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
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    
    //// ����(��) ��ǥ�� -> ���� -> �� -> ���� ��ǥ��� ���������� ��ȯ
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
    //float4 vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    
    //if (g_int_0)
    //{
    //    vColor = float4(1.f, 1.f, 1.f, 1.f);
    //}
    
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    if (g_btex_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        
        float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);
        
        if (fAlpha<0.1f)
            discard;
    }
    
        return vColor;
}

#endif
