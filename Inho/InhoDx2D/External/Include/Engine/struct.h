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
};