#ifndef _STRUCT
#define _STRUCT
// =======================================
// struct.fx: struct type ����
// =======================================

struct tLightColor
{
    float4 vColor; // ���� ����		(������ ���� ����)
    float4 vSpecular; // �ݻ籤			(������ ��ü ǥ�鿡 �ݻ�Ǵ� ����)
    float4 vAmbient; // ȯ�汤(�ֺ���)	(������ ���� ����Ǵ� �ּ����� ��)
};

struct tLightInfo
{
    int LightType;      // ���� Ÿ��
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