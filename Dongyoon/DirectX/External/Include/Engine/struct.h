#pragma once


//3차원 공간에 배치되는 정점
struct Vtx
{
	Vec3 vPos;
	Vec4 vColor;
	Vec2 vUV;			//UV 좌표계 OR Texture Coodinate
};

struct tDebugShapeInfo
{
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

struct tPixel
{
	BYTE r, g, b, a;
};

struct tParticle
{
	Vec4 vLocalPos; // 로컬 위치
	Vec4 vWorldPos; // 월드 위치
	Vec4 vWorldInitScale; // 초기 크기
	Vec4 vWorldScale; // 크기
	Vec4 vWorldRotation; // 회전값
	Vec3 vVelocity; // 속도
	Vec4 vColor; // 색상
	Vec4 vForce; // 입자에 누적된 누적 힘 총량
	Vec3 vNoiseForce; // NoiseForce 모듈로 인한 랜덤 힘
	float NoiseForceTime; //NoiseForce를 세팅받은 시간

	float NormalizeAge; //Age를 Life 기준으로 정규화 한 값
	float Mass; //질량
	float Age; // 현재 나이
	float Life; // 수명
	int Active; //활성화 비활성화 여부

};

struct tParticleModule
{
	//Spawn 모듈
	Vec4	vSpawnColor; // 초기 컬러
	Vec4	vSpawnMinScale; // 초기 최소 크기
	Vec4	vSpawnMaxScale; // 초기 최대 크기

	float MinLife; // 최소 수명
	float MaxLife; // 최대 수명
	float MinMass; // 최소 질량
	float MaxMass; // 최대 질량
	int SpawnRate; // 초당 생성 개수
	int SpaceType; // 좌표계(0 : LocalSpace, 1 : WorldSpace)
	int SpawnShape; // 스폰 범위(0 : Sphere, 1 : Box)
	float Radius; // SpawnShape 가 Sphere 인 경우, 반지름 길이
	Vec4 vSpawnBoxScale; //SpawnShape가 Box인 경우, Box의 크기
	Vec2 padding;

	// Add Velocity
	int AddVelocityType; // 0: From Center, 1 : To Center, 2: Fix Direction
	float MinSpeed;
	float MaxSpeed;
	float FixedAngle; // 해당 방향에서 랜덤 범위 각도
	Vec4 FixedDirection; // 지정 방향

	//Scale
	Vec4 vScaleRatio;

	//Noise Force
	float NoiseForceScale;
	float NoiseForceTerm;

	// Render
	int		VelocityAlignment; // 1 : On, 0: Off
	int		AlphaBaseLife; // 0 : off, 1: NormalizedAge, 2: Age
	float	AlphaMaxAge;

	//Module On / Off
	int arrModuleCheck[(UINT)PARTICLE_MODULE::END];

};

struct tSpawnCount
{
	int SpawnCount;
	int iPadding[3];
};
//======================
//상수 버퍼 대응 구조체
//=======================
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

	int bTex[TEX_PARAM::END];

	int iPadding[2];

};

struct tAnimData2D
{
	Vec2 vLeftTop;
	Vec2 vSlizeSize;
	Vec2 vBackGround;
	Vec2 vOffset;
	int  UseAnim2D;
	Vec3 vPadding;
};

struct tGlobalData
{
	Vec2 g_RenderResolution;
	Vec2	g_NoiseTexResolution;
	float g_dt;
	float g_time;
	int g_Light2DCount;
	int g_Light3DCount;

};

extern tGlobalData g_global;