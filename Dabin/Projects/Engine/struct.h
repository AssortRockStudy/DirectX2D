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

// Constant Buffer ���� ����ü
// - constant buffer�� ������ ���� �ݵ�� 16Byte ũ�� ���
struct tTransform
{
	Matrix matWorld;
};