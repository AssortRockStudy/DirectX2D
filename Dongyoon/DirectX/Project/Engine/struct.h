#pragma once


//3���� ������ ��ġ�Ǵ� ����
struct Vtx
{
	Vec3 vPos;
	Vec4 vColor;
	Vec2 vUV;			//UV ��ǥ�� OR Texture Coodinate
};

//======================
//��� ���� ���� ����ü
//=======================
struct tTransform
{
	Vec4 vWorldPos;
	Vec4 vWorldScale;
};