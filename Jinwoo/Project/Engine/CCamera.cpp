#include "pch.h"
#include "CCamera.h"

#include "CDevice.h"
#include "CTransform.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_ProjType(PROJ_TYPE::PERSPECTIVE)
	, m_FOV(XM_PI / 2.f)
	, m_Width(0.f)
	, m_Scale(1.f)
	, m_AspectRatio(1.f)
	, m_Far(10000.f)
{
	Vec2 vResol = CDevice::GetInst()->GetRenderResolution();
	m_AspectRatio = vResol.x / vResol.y;
}

CCamera::~CCamera()
{
}


void CCamera::finaltick()
{
	// 뷰 행렬을 계산
	Vec3 vCamPos = Transform()->GetRelativePos();
	Matrix matTrans = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);

	// 카메라의 각 오른쪽, 위, 앞 방향을 기본축이랑 일치시키도록 회전하는 회전행렬
	Vec3 vRight = Transform()->GetDir(DIR_TYPE::RIGHT);
	Vec3 vUp = Transform()->GetDir(DIR_TYPE::UP);
	Vec3 vFront = Transform()->GetDir(DIR_TYPE::FRONT);

	// 회전행렬의 역행렬
	Matrix matRotate = XMMatrixIdentity();

	matRotate._11 = vRight.x;	matRotate._12 = vUp.x;	matRotate._13 = vFront.x;
	matRotate._21 = vRight.y;	matRotate._22 = vUp.y;	matRotate._23 = vFront.y;
	matRotate._31 = vRight.z;	matRotate._32 = vUp.z;	matRotate._33 = vFront.z;

	// 이동 * 회전 = view 행렬 (이동 -> 회전 순서 주의)
	m_matView = matTrans * matRotate;

	// 투영 방식에 따른 투영 행렬을 계산
	m_matProj = XMMatrixIdentity();

	// 직교 투영일 때
	if (m_ProjType == PROJ_TYPE::ORTHOGRAPHIC)
	{
		Vec2 vResol = CDevice::GetInst()->GetRenderResolution();
		m_matProj = XMMatrixOrthographicLH(vResol.x * m_Scale, (vResol.x / m_AspectRatio) * m_Scale, 1.f, m_Far);
	}
	// 원근 투영일 때
	else
	{
		m_matProj = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, 1.f, m_Far);
	}

	// 계산한 view 행렬과 proj 행렬을 전역변수에 담아둔다
	g_Transform.matView = m_matView;
	g_Transform.matProj = m_matProj;
}