#pragma once

// 정점
// - 정점은 좌표 외 다양한 정보를 가지고 있을 수 있음
// - Normal Vector 법선벡터, Tangent Vector 접선벡터, BiNormal Vector ...
struct Vtx
{
	Vec3 vPos;		// 정점 좌표
	Vec4 vColor;	// 색상 정보
	Vec2 vUV;		// UV 좌표계 or Texture Coodinate
};

struct FDebugShapeInfo
{
	DEBUG_SHAPE	ShapeType;
	Vec3		vWorldPos;
	Vec3		vWorldScale;
	Vec3		vWorldRot;
	Matrix		matWorld;

	Vec3		vColor;
	float		fLifeTime;
	float		fDuration;
	bool		bDepthTest;
};

struct FLightInfo
{
	int		LightType;	// 광원 타입
	Vec4	vColor;		// 빛의 색상		(광원의 순수 색상)
	Vec4	vSpecular;	// 반사광			(광원이 물체 표면에 반사되는 색상)
	Vec4	vAmbient;	// 환경광(주변광)	(광원에 의해 보장되는 최소한의 빛)

	Vec3	vWorldPos;
	Vec3	vWorldDir;
	float	fRadius;
	float	fAngle;

	Vec3	vPadding;
};

struct FPixel
{
	BYTE r, g, b, a;
};

// FParticle: 입자 하나가 가지는 정보를 담은 구조체
struct FParticle
{
	Vec4	vWorldPos;
	Vec4	vWorldScale;
	Vec4	vWorldRotation;
	Vec4	vVelocity;
	Vec4	vColor;

	float	Mass;
	float	Age;
	float	Life;
	int		Active;
};

// FParticleModule: Particle System의 세팅을 담은 구조체
struct FParticleModule
{
	// Module: Spawn
	Vec4	vSpawnColor;
	Vec4	vSpawnScaleMin;
	Vec4	vSpawnScaleMax;

	float	LifeMin;
	float	LifeMax;
	int		SpawnRate;
	int		SpaceType;			// 좌표계 (0: Local, 1: World)
};

// FSpawnCount: Particle Spawn 동기화에 사용
struct FSpawnCount
{
	int SpawnCount;
	int iPadding[3];
};

//---------------------------------
// Constant Buffer 대응 구조체
//---------------------------------
// - constant buffer는 정렬을 위해 반드시 16Byte 크기 사용
struct FTransform
{
	Matrix matWorld;
	Matrix matWorldInv;

	Matrix matView;
	Matrix matViewInv;

	Matrix matProj;
	Matrix matProjInv;

	Matrix matWV;	// World * View
	Matrix matWVP;	// World * View * Proj
};
extern FTransform g_Transform;	// 외부 변수 (전역 변수)

// tMatrlConst: material에서 사용할 params 모아둔 구조체
// SCALAR_PARAM: define const paramater type that can be transffered to mateiral
struct FMtrlConst
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matArr[4];

	// texture binding 여부 전달
	int bTex[(UINT)TEX_PARAM::END];

	int iPadding[2];
};

struct FAnimData2D
{
	Vec2 vLeftTop;
	Vec2 vCutSize;
	Vec2 vBackgroundSize;
	Vec2 vOffset;
	int UseAnim2D;
	Vec3 vPadding;
};

struct FGlobalData		// 자주 사용하는 정보들 전달
{
	Vec2	g_RenderResolution;
	float	g_dt;
	float	g_time;
	int		g_Light2DCount;
	int		g_Light3DCount;
	Vec2	g_vPadding;
};
extern FGlobalData g_Global;