#ifndef _STRUCT
#define _STRUCT
// =======================================
// struct.fx: struct type 정의
// =======================================

struct tLightColor
{
    float4 vColor; // 빛의 색상		(광원의 순수 색상)
    float4 vSpecular; // 반사광			(광원이 물체 표면에 반사되는 색상)
    float4 vAmbient; // 환경광(주변광)	(광원에 의해 보장되는 최소한의 빛)
};

struct tLightInfo
{
    int LightType;      // 광원 타입
    tLightColor Color;

    float3 vWorldPos;
    float3 vWorldDir;
    float fRadius;
    float fAngle;

    float3 vPadding;
};

struct FTileInfo
{
    float2  vLeftTopUV;
    int     bRender;
    int     padding;
};


struct FParticle
{
    float4  vWorldPos;
    float4  vWorldScale;
    float4  vWorldRotation;
    float4  vVelocity;
    float4  vColor;

    float   Mass;
    float   Age;
    float   Life;
    int     Active;
};


#endif