#ifndef _STRUCT
#define _STRUCT

struct tLightColor
{
    float4 vColor;
    float4 vSpecular;
    float4 vAmbient;
};

struct tLightInfo
{
    tLightColor Color;
    
    float3 vWorldPos;
    float3 vWorldDir;
    float fRadius;
    float fAngle;
    
    int LightType;
    float3 vPadding;
};

struct tTileInfo
{
    float2 vLeftTopUV;
    int bRender;
    int padding;
};

struct tParticle
{
    float4 vWorldPos; // ��ġ
    float4 vWorldScale; // ũ��
    float4 vWorldRotation; // ȸ����
    float4 vVelocity; // �ӵ�
    float4 vColor; // ����

    float Mass; // ����
    float Age; // ���� ����
    float Life; // ����
    int Active; // Ȱ��ȭ, ��Ȱ��ȭ ����
};

struct tSpawnModule
{
	// ���� ���
    float4 vSpawnColor;
    float4 vSpawnMinScale;
    float4 vSpawnMaxScale;

    float MinLife;
    float MaxLife;
    int SpawnRate; // �ʴ� ���� ����
    int SpaceType; // ��ǥ��( 0: LocalSpace, 1: WorldSpace)
    int SpawnShape; // ���� ���� (0: Sphere, 1: WorldSpace)
    float Radius;
    float4 vSpawnBoxScale;
    float2 padding;
};

struct tParticleModule
{
    tSpawnModule SpawnModule;
    
    int arrModuleCheck[4];
};

struct tSpawnCount
{
    int iSpawnCount;
    int3 iPadding;
};

#endif