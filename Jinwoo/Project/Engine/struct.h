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