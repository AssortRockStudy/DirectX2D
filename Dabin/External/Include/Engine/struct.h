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

struct tDebugShapeInfo
{
	DEBUG_SHAPE	ShapeType;
	Vec3		vWorldPos;
	Vec3		vWorldScale;
	Vec3		vWorldRot;
	Matrix		matWorld;

	Vec3		vColor;
	float		fDuration;
	bool		bDepthTest;
};


//---------------------------------
// Constant Buffer 대응 구조체
//---------------------------------
// - constant buffer는 정렬을 위해 반드시 16Byte 크기 사용
struct tTransform
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
extern tTransform g_Transform;	// 외부 변수 (전역 변수)

// tMatrlConst: material에서 사용할 params 모아둔 구조체
// SCALAR_PARAM: define const paramater type that can be transffered to mateiral
struct tMtrlConst
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
