#include "pch.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CDevice.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_ProjType(PROJ_TYPE::PERSEPECTIVE)
	, m_FOV(XM_PI/2.f)	// 90도
	, m_Width(0.f)
	, m_Scale(1.f)
	, m_AspectRatio(1.f)
	, m_Far(10000.f)
{
	Vec2 vRes = CDevice::GetInst()->GetRenderResolution();
	m_AspectRatio = vRes.x / vRes.y;
}

CCamera::~CCamera()
{
}

void CCamera::finaltick()
{
	// view matrix
	Vec3 vCamPos = Transform()->GetRelativePos();
	Vec3 vRight = Transform()->GetDir(DIR_TYPE::RIGHT);
	Vec3 vUp	= Transform()->GetDir(DIR_TYPE::UP);
	Vec3 vFront = Transform()->GetDir(DIR_TYPE::FRONT);

	Matrix matTrans = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);
	Matrix matRot = XMMatrixIdentity(); // cam dir의 역행렬 (cam dir을 coord에 일치시킴)
	matRot._11 = vRight.x; matRot._12 = vUp.x; matRot._13 = vFront.x;
	matRot._21 = vRight.y; matRot._22 = vUp.y; matRot._23 = vFront.y;
	matRot._31 = vRight.z; matRot._32 = vUp.z; matRot._33 = vFront.z;

	m_matView = matTrans * matRot;	// translation -> rotation = view matrix

	// projection matrix
	m_matProj = XMMatrixIdentity();

	if (m_ProjType == PROJ_TYPE::ORTHGRAPHIC)
	{
		Vec2 vRes = CDevice::GetInst()->GetRenderResolution();
		m_matProj = XMMatrixOrthographicLH(vRes.x * m_Scale, (vRes.x / m_AspectRatio) * m_Scale, 1.f, m_Far); // LH: LeftHand Coord
	}
	else
		m_matProj = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, 1.f, m_Far);

	g_Transform.matView = m_matView;
	g_Transform.matProj = m_matProj;
}
