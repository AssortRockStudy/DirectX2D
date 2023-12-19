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

// Constant Buffer 대응 구조체
// - constant buffer는 정렬을 위해 반드시 16Byte 크기 사용
struct tTransform
{
	Matrix matWorld;
};