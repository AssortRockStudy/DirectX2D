#ifndef _STD2D
#define _STD2D

#include "value.fx"

struct VS_IN
{
    float4 vColor : COLOR;
    float3 vPos : POSITION; // Sementic
    float2 vUV : TEXCOORD;
    // 다이렉트 기준 UV 좌표계는
    // 좌상단 (0,0), 우하단이 (1,1)인 사각형으로 가진다
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
    
    // 로컬(모델) 좌표 -> 월드 좌표 -> 뷰 좌표 -> 투영 좌표계 순서로 순차적으로 변환
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    // t9 이상에 텍스처를 등록하고 테스트할 땐
    // 해상도만큼의 픽셀에서 정보를 가져오는 것이 더 편할 때가 있다
    // uint width = 0;
    // uint height = 0;
    // g_tex_1.GetDimensions(width, height);
    
    // 텍스처 g_tex_0에서 _in.vUV 좌표에 해당하는 픽셀을 샘플링하는 연산
    // vColor는 샘플링 이후의 픽셀이 가진 색상 값을 나타낸다
    // float4 vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    
    // 흑백
    // float Aver = (vColor.r + vColor.g + vColor.b) / 3.f;
    // vColor.rgb = float3(Aver, Aver, Aver);    
    // vColor.a = 1.f;
    
    float4 vColor = float4(1.f, 0.f, 1.f, 1.f);
    
    if(g_btex_0)
    {
        vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
        
        // saturate : 0 ~ 1을 넘지않게 보정
        float fAlpha = 1.f - saturate(dot(vColor.rb, vColor.rb) / 2.f);

        if(fAlpha < 0.1f)
        {
            // 픽셀 셰이더를 중간에 폐기 처리
            discard;    // clip(-1)로도 동일하게 작동 가능
        }
    }
    
    // 픽셀로 들어올 때 정점의 위치에 맞게 보간된다
    return vColor;
}


#endif