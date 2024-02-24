#pragma once

struct Vtx {
	Vec3 vPos;
	Vec4 vColor;
	Vec2 vUV;
};

struct tDebugShapeInfo {
	DEBUG_SHAPE eShape;

	Vec3 vWorldPos;
	Vec3 vWorldScale;
	Vec3 vWorldRot;
	Matrix matWorld;

	Vec3 vColor;
	float fLifeTime;
	float fDuration;
	bool bDepthTest;

};

struct tLightInfo {
	Vec4 vColor;
	Vec4 vSpecular;
	Vec4 vAmbient;

	Vec3 vWorldPos;
	Vec3 vWorldDir;
	float fRadius;
	float fAngle;

	int LightType;

	Vec3 vPadding;
};

struct tPixel {
	BYTE r, g, b, a;
};

struct tParticle {
	Vec4 vLocalPos;
	Vec4 vWorldPos;
	Vec4 vWorldScale;
	Vec4 vWorldRotation;
	Vec4 vVelocity;
	Vec4 vColor;

	float Mass;
	float Age;
	float Life;
	int Active;
};

struct tSpawnModule {
	// 스폰 모듈
	Vec4 vSpawnColor;
	Vec4 vSpawnMinScale;
	Vec4 vSpawnMaxScale;

	float MinLife;
	float MaxLife;
	int SpawnRate; // 초당 생성 개수
	int SpaceType; // 좌표계( 0: LocalSpace, 1: WorldSpace)
	int SpawnShape; // 스폰 범위 (0: Sphere, 1: WorldSpace)
	float Radius;
	Vec4 vSpawnBoxScale;
	Vec2 padding;
};

struct tVelocityModule
{
	int AddVelocityType; // 0: FromCenter, 1: To Center, 2: FixDirection
	float MinSpeed; 
	float MaxSpeed;
	float FixedAngle;
	Vec4 FixedDirection;
};

struct tParticleModule {
	tSpawnModule SpawnModule;
	tVelocityModule VelocityModule;
	int arrModuleCheck[(UINT)PARTICLE_MODULE::END];
};

struct tSpawnCount {
	int SpawnCount;
	int vPadding[3];
};

// ==================
// 상수버퍼 대응 구조체
// ==================
struct tTransform
{
	Matrix matWorld;
	Matrix matWorldInv;

	Matrix matView;
	Matrix matViewInv;

	Matrix matProj;
	Matrix matProjInv;

	Matrix matWV;
	Matrix matWVP;
};

extern tTransform g_Transform;

struct tMtrlConst {
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matArr[4];

	int bTex[TEX_PARAM::END];

	int iPadding[2];
};

struct tAnimData2D {
	Vec2 vLeftTop;
	Vec2 vSliceSize;
	Vec2 vBackGround;
	Vec2 vOffset;
	int UseAnim2D;
	Vec3 vPadding;
};

struct tGlobalData {
	Vec2 g_RenderResolution;
	float g_dt;
	float g_time;
	int g_Light2DCount;
	int g_Light3DCount;
	Vec2 g_vPaading;
};
extern tGlobalData g_global;