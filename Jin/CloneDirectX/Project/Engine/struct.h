#pragma once

// 3차원 공간에 배치되는 정점
struct Vtx
{
	Vec3 vPos;		 // 정점의 좌표
	Vec4 vColor;	 // 정점의 색상 정보
	Vec2 vUV;		 // UV 좌표계 or Texture Coodinate
};

struct tDebugShapeInfo
{
	DEBUG_SHAPE 	eShape;

	Vec3		vWorldPos;
	Vec3		vWorldScale;
	Vec3		vWorldRot;
	Matrix		matWorld;

	Vec3		vColor;
	float		fLifeTime;
	float		fDuration;
	bool		bDepthTest;
};


struct tTransform
{
	Matrix	matWorld;
	Matrix	matWorldInv;

	Matrix	matView;
	Matrix	matViewInv;

	Matrix	matProj;
	Matrix	matProjInv;

	Matrix	matWV;
	Matrix	matWVP;
};

extern tTransform g_Transform;

struct tMtrlConst
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matArr[4];

	int	bTex[TEX_PARAM::END];
	int iPadding[2];
};

struct tAnimData2D
{
	Vec2 vLeftTop;
	Vec2 vSlizeSize;
	Vec2 vBackGround;
	Vec2 vOffset;
	int  UseAnim2D;

	Vec3 iPadding;
};

struct tLightInfo
{
	Vec4	vColor;		// 빛의 색상	- 광원의 순수 색상
	Vec4	vSpecular;	// 반사광	- 광원이 물체 표변에 반사된 색상
	Vec4	vAmbient;	// 환경광(주변광) - 광원에 의해서 보장되는 최소한의 빛

	Vec3	vWorldPos;	// 광원의 위치
	Vec3	vWorldDir;	// 광원이 향하는 방향
	float	fRadius;	// 광원의 영향 반경, 거리 정보
	float	fAngle;		// 광원의 범위 각도

	int		LightType;	// 광원 타입

	Vec3	vPadding;
};

struct tGlobalData
{
	Vec2	g_RenderResolution;	// 렌더링 해상도
	float	g_dt;				// Delta Time
	float	g_time;				// 누적 시간
	int		g_Light2DCount;		// 2D 광원 개수
	int		g_Light3DCount;		// 3D 광원 개수
	Vec2	g_vPadding;
};
extern tGlobalData g_global;