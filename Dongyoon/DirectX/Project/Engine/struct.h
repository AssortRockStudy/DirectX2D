#pragma once


//3차원 공간에 배치되는 정점
struct Vtx
{
	Vec3 vPos;
	Vec4 vColor;
	Vec2 vUV;			//UV 좌표계 OR Texture Coodinate
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