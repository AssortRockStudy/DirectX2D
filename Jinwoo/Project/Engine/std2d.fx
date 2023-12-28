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

// 그냥 int arr[4]로 설정할 경우, 16바이트로 설정되어 있기 때문에
// 4바이트 배열 4개를 만드는 것이 아닌 16바이트 배열 4개를 만든다
cbuffer MATERIAL_CONST : register(b1)
{
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;
    
    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;
    
    float2 g_vec2_0;
    float2 g_vec2_1;
    float2 g_vec2_2;
    float2 g_vec2_3;
    
    float4 g_vec4_0;
    float4 g_vec4_1;
    float4 g_vec4_2;
    float4 g_vec4_3;
    
    row_major matrix g_mat_0;
    row_major matrix g_mat_1;
    row_major matrix g_mat_2;
    row_major matrix g_mat_3;
    
    int g_btex_0;
    int g_btex_1;
    int g_btex_2;
    int g_btex_3;
    int g_btex_4;
    int g_btex_5;
   
    int g_btexcube_0;
    int g_btexcube_1;
    
    int g_btexarr_0;
    int g_btexarr_1;
}

// register(t0)에 등록된 텍스처 객체
Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);
Texture2D g_tex_4 : register(t4);
Texture2D g_tex_5 : register(t5);

TextureCube g_texcube_0 : register(t6);
TextureCube g_texcube_1 : register(t7);

Texture2DArray g_texarr_0 : register(t8);
Texture2DArray g_texarr_1 : register(t9);


// register(s0)에 등록된 샘플러
// 샘플링은 텍스처에서 특정 위치의 값을 읽어오는 과정으로
// 이미지 데이터를 저장하고 있는 텍스처를 텍스처 좌표(일반적으로 UV좌표)를 사용하여
// 이미지의 특정 위치에 해당하는 색상 값을 가져오는 과정이다
SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);

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