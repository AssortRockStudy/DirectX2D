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