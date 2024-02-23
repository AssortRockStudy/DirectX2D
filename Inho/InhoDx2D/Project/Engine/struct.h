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