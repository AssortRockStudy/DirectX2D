#ifndef _POSTPROCESS
#define _POSTPROCESS

#include "value.fx"

// mesh : RectMesh
struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};


// GrayFilter
VS_OUT VS_GrayFilter(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // 로컬 스페이스에 2배를 하면 전체화면의 해상도와 같다
    output.vPosition = float4(_in.vPos * 2.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_GrayFilter(VS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
            
    vColor = g_postprocess.Sample(g_sam_0, _in.vUV);
    
    float aver = (vColor.r + vColor.g + vColor.b) / 3.f;
    
    vColor.rgb = float3(aver, aver, aver);
    
    return vColor;
}



// Distortion
VS_OUT VS_Distortion(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Distortion(VS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
        
    // 픽셀 셰이더에 SV_Position으로 입력된 값은 픽셀 셰이더를 호출한 해당 픽셀의 좌표가 들어있음
    float2 vScreenUV = _in.vPosition.xy / g_RenderResolution;
    
    ////                                  시간      속도 / 주파수 / 진폭
    //vScreenUV.y += cos((vScreenUV.x + (g_time * 0.1f)) * 3.f) * 0.1f;
    
    if(g_btex_0)
    {
        float vUV = _in.vUV;
        vUV.x += g_time * 0.1f;
        
        float2 vNoise = g_tex_0.Sample(g_sam_0, vUV);
        vNoise = (vNoise.xy - 0.5f) * 0.03f;
 
        vScreenUV += vNoise;
    }
    
    vColor = g_postprocess.Sample(g_sam_0, vScreenUV);
    
    return vColor;
}



#endif