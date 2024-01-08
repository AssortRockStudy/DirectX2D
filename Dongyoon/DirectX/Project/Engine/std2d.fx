#ifndef _STD2D
#define _STD2D

// 4096ũ�� ����
cbuffer TRNASFORM : register(b0)
{
    row_major matrix g_matWorld;
    row_major matrix g_matWorldInv;
    
    row_major matrix g_matView;
    row_major matrix g_matViewInv;
    
    row_major matrix g_matProj;
    row_major matrix g_matProjInv;
    
    row_major matrix g_matWV;
    row_major matrix g_matWVP;
}

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
}

Texture2D g_tex_0 : register(t0);


SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);

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
    
 
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 vColor = g_tex_0.Sample(g_sam_1, _in.vUV);

   //if(vColor.a <= 0.1f)
   //{
   //  vColor.rgba = float4(1.f, 0.f, 0.f, 1.f);
   //}
    
    
   // float Aver = (vColor.r + vColor.g + vColor.b) / 3.f;
   //vColor.rgb = float3(Aver, Aver, Aver);
   //vColor.a = 1.f;
    
    
   if(g_int_0)
   {
       vColor = float4(1.f, 0.f, 1.f, 1.f);
   }
    
    return vColor;

}


#endif
