#pragma once

// ����
// - ������ ��ǥ �� �پ��� ������ ������ ���� �� ����
// - Normal Vector ��������, Tangent Vector ��������, BiNormal Vector ...
struct Vtx
{
	Vec3 vPos;		// ���� ��ǥ
	Vec4 vColor;	// ���� ����
	Vec2 vUV;		// UV ��ǥ�� or Texture Coodinate
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
	int		LightType;	// ���� Ÿ��
	Vec4	vColor;		// ���� ����		(������ ���� ����)
	Vec4	vSpecular;	// �ݻ籤			(������ ��ü ǥ�鿡 �ݻ�Ǵ� ����)
	Vec4	vAmbient;	// ȯ�汤(�ֺ���)	(������ ���� ����Ǵ� �ּ����� ��)

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

// FParticle: ���� �ϳ��� ������ ������ ���� ����ü
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

// FParticleModule: Particle System�� ������ ���� ����ü
struct FParticleModule
{
	// Module: Spawn
	Vec4	vSpawnColor;
	Vec4	vSpawnScaleMin;
	Vec4	vSpawnScaleMax;

	float	LifeMin;
	float	LifeMax;
	int		SpawnRate;
	int		SpaceType;			// ��ǥ�� (0: Local, 1: World)
};

// FSpawnCount: Particle Spawn ����ȭ�� ���
struct FSpawnCount
{
	int SpawnCount;
	int iPadding[3];
};

//---------------------------------
// Constant Buffer ���� ����ü
//---------------------------------
// - constant buffer�� ������ ���� �ݵ�� 16Byte ũ�� ���
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
extern FTransform g_Transform;	// �ܺ� ���� (���� ����)

// tMatrlConst: material���� ����� params ��Ƶ� ����ü
// SCALAR_PARAM: define const paramater type that can be transffered to mateiral
struct FMtrlConst
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matArr[4];

	// texture binding ���� ����
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

struct FGlobalData		// ���� ����ϴ� ������ ����
{
	Vec2	g_RenderResolution;
	float	g_dt;
	float	g_time;
	int		g_Light2DCount;
	int		g_Light3DCount;
	Vec2	g_vPadding;
};
extern FGlobalData g_Global;