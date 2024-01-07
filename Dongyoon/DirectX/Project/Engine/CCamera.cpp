#include "pch.h"
#include "CCamera.h"

#include "CDevice.h"
#include "CTransform.h"



CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_ProjType(PROJ_TYPE::PERSPECTIVE)
	, m_Fov(XM_PI / 2.f)
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
	// 뷰 행렬 계산
	// 카메라를 원점으로 이동시키는 이동행렬
	Vec3 vCamPos = Transform()->GetRelativePos();
	Matrix matTrans = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);

	// 카메라의 각 우, 상, 전 방 방향을 기저축이랑 일치시키도록 회전하는 회전행렬
	Vec3 vRight = Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	Vec3 vUp = Transform()->GetWorldDir(DIR_TYPE::UP);;
	Vec3 vFront = Transform()->GetWorldDir(DIR_TYPE::FRONT);;


	Matrix matRotate = XMMatrixIdentity();

	matRotate._11 = vRight.x; matRotate._12 = vUp.x; matRotate._13 = vFront.x;
	matRotate._21 = vRight.y; matRotate._22 = vUp.y; matRotate._23 = vFront.y;
	matRotate._31 = vRight.z; matRotate._32 = vUp.z; matRotate._33 = vFront.z;
	
	m_matView = matTrans * matRotate;

	// 투영 방식에 따른 투영 행렬 계산
	m_matProj = XMMatrixIdentity();

	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType)
	{
		Vec2 vResol = CDevice::GetInst()->GetRenderResolution();
		m_matProj = XMMatrixOrthographicLH(vResol.x * m_Scale, (vResol.x / m_AspectRatio) * m_Scale, 1.f, m_Far);
	}
	else
	{
		//원근투영
		m_matProj = XMMatrixPerspectiveFovLH(m_Fov, m_AspectRatio, 1.f, m_Far);
	}

	//계산한 view 행렬과 proj 행렬을 전역변수에 담아둔다.
	g_Transform.matView = m_matView;
	g_Transform.matProj = m_matProj;
}