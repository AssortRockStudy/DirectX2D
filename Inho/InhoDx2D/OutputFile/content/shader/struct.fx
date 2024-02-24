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
    float4 vWorldPos; // 위치
    float4 vWorldScale; // 크기
    float4 vWorldRotation; // 회전값
    float4 vVelocity; // 속도
    float4 vColor; // 색상

    float Mass; // 질량
    float Age; // 현재 나이
    float Life; // 수명
    int Active; // 활성화, 비활성화 여부
};

struct tSpawnModule
{
	// 스폰 모듈
    float4 vSpawnColor;
    float4 vSpawnMinScale;
    float4 vSpawnMaxScale;

    float MinLife;
    float MaxLife;
    int SpawnRate; // 초당 생성 개수
    int SpaceType; // 좌표계( 0: LocalSpace, 1: WorldSpace)
    int SpawnShape; // 스폰 범위 (0: Sphere, 1: WorldSpace)
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