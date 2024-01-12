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
// Constant Buffer ���� ����ü
//---------------------------------
// - constant buffer�� ������ ���� �ݵ�� 16Byte ũ�� ���
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
extern tTransform g_Transform;	// �ܺ� ���� (���� ����)

// tMatrlConst: material���� ����� params ��Ƶ� ����ü
// SCALAR_PARAM: define const paramater type that can be transffered to mateiral
struct tMtrlConst
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
