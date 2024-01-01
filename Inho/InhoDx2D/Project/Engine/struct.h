#pragma once

struct Vtx {
	Vec3 vPos;
	Vec4 vColor;
	Vec2 vUV;
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