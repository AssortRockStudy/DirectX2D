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
    float4 vLocalPos;
    float4 vWorldPos; // ��ġ
    float4 vWorldInitScale;
    float4 vWorldScale; // ũ��
    float4 vWorldRotation; // ȸ����
    float3 vVelocity; // �ӵ�
    float4 vColor; // ����
    float4 vForce;

    float NormalizedAge;
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
    float MinMass;
    float MaxMass;
    int SpawnRate; // �ʴ� ���� ����
    int SpaceType; // ��ǥ��( 0: LocalSpace, 1: WorldSpace)
    int SpawnShape; // ���� ���� (0: Sphere, 1: WorldSpace)
    float Radius;
    float4 vSpawnBoxScale;
};

struct tVelocityModule
{
    int AddVelocityType; // 0: FromCenter, 1: To Center, 2: FixDirection
    float MinSpeed;
    float MaxSpeed;
    float FixedAngle;
    float4 FixedDirection;
};

struct tScaleModule
{
    float4 vScaleRatio;
};

struct tNoiseForce
{
    float NoiseForceScale;
};
struct tParticleModule
{
    tSpawnModule SpawnModule;
    tVelocityModule VeloctiyModule;
    
    tScaleModule ScaleModule;
    tNoiseForce NoiseForce;
    int arrModuleCheck[6];
};

struct tSpawnCount
{
    int iSpawnCount;
    int3 iPadding;
};

#endif