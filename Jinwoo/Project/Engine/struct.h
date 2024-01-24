#pragma once


// 3차원 공간에 배치되는 정점
struct Vtx
{
	Vec3 vPos;		 // 정점의 좌표
	Vec4 vColor;	 // 정점의 색상 정보
	Vec2 vUV;		 // UV 좌표계 or Texture Coodinate
};


// 상수버퍼 대응 구조체
// 상수버퍼는 16바이트씩 데이터를 읽기 때문에 구조체 크기를 16바이트의 배수로 맞춰야 한다
// 오브젝트의 상태값을 행렬에 모두 담는다
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

struct tMtrlConst
{
	int		iArr[4];
	float	fArr[4];
	Vec2	v2Arr[4];
	Vec4	v4Arr[4];
	Matrix	matArr[4];

	int		bTex[TEX_PARAM::END];

	int		iPadding[2];
};

struct tDebugShapeInfo
{
	DEBUG_SHAPE eShape;
	
	Vec3	vWorldPos;
	Vec3	vWorldScale;
	Vec3	vWorldRot;
	Matrix	matWorld;

	Vec3	vColor;
	float	fLifeTime;
	float	fDuration;
	bool	bDepthTest;
};

struct tAnimData2D
{
	Vec2	vLeftTop;
	Vec2	vSliceSize;
	Vec2	vOffset;
	Vec2	vBackground;
	int		UseAnim2D;
	Vec3	iPadding;
};

struct tLightInfo
{
	Vec4	vColor;		// 광원의 순수 색상
	Vec4	vSpecular;	// 반사광 - 광원이 물체 표면에 반사된 색상
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
	Vec2	g_RenderResolution;		// 렌더링 해상도
	float	g_dt;					// 델타 타임
	float	g_time;					// 누적 시간
	int		g_Light2DCount;			// 2D 광원 개수
	int		g_Light3DCount;			// 3D 광원 개수
	Vec2	g_vPadding;
};

extern tGlobalData g_global;


struct tAnimFrm
{
	Vec2 vLeftTop;
	Vec2 vSlice;
	Vec2 vOffset;
	Vec2 vBackground;
	float Duration;
};

struct tPixel
{
	BYTE r, g, b, a;
};

struct tParticle
{
	Vec4	vWorldPos;		// 위치
	Vec4	vWorldScale;	// 크기
	Vec4	vWorldRotation;	// 회전
	Vec4	vVelocity;		// 속도
	Vec4	vColor;			// 색상

	float	Mass;			// 질량
	float	Age;			// 현재 나이
	float	Life;			// 수명
	int		Active;			// 활성화, 비활성화
};