#ifndef _STD2D
#define _STD2D

// register 크기 제한 4096
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

// register(t0)에 등록된 텍스처 객체
Texture2D g_tex_0 : register(t0);

// register(s0)에 등록된 샘플러
// 샘플링은 텍스처에서 특정 위치의 값을 읽어오는 과정으로
// 이미지 데이터를 저장하고 있는 텍스처를 텍스처 좌표(일반적으로 UV좌표)를 사용하여
// 이미지의 특정 위치에 해당하는 색상 값을 가져오는 과정이다
SamplerState g_sam_0 : register(s0);

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
    // 텍스처 g_tex_0에서 _in.vUV 좌표에 해당하는 픽셀을 샘플링하는 연산
    // vColor는 샘플링 이후의 픽셀이 가진 색상 값을 나타낸다
    float4 vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    
    // 흑백
    // float Aver = (vColor.r + vColor.g + vColor.b) / 3.f;
    // vColor.rgb = float3(Aver, Aver, Aver);    
    // vColor.a = 1.f;
    
    // 픽셀로 들어올 때 정점의 위치에 맞게 보간된다
    return vColor;
}


#endif