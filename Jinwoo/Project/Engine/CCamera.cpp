#include "pch.h"
#include "CCamera.h"

#include "CDevice.h"
#include "CTransform.h"
#include "CRenderMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_ProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_FOV(XM_PI / 2.f)
	, m_Width(0.f)
	, m_Scale(1.f)
	, m_AspectRatio(1.f)
	, m_Far(10000.f)
	, m_LayerCheck(0)
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
	Vec3 vRight = Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	Vec3 vUp = Transform()->GetWorldDir(DIR_TYPE::UP);
	Vec3 vFront = Transform()->GetWorldDir(DIR_TYPE::FRONT);

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
}

void CCamera::render()
{
	// 계산한 view 행렬과 proj 행렬을 전역변수에 담아둔다
	g_Transform.matView = m_matView;
	g_Transform.matProj = m_matProj;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	for (int i = 0; i < LAYER_MAX; ++i)
	{
		// 카메라가 찍도록 설정된 Layer가 아니면 무시
		if (false == (m_LayerCheck & (1 << i)))
		{
			continue;
		}

		CLayer* pLayer = pCurLevel->GetLayer(i);
		const vector<CGameObject*>& vecObjects = pLayer->GetLayerObjects();

		for (size_t i = 0; i < vecObjects.size(); ++i)
		{
			vecObjects[i]->render();
		}
	}
}


void CCamera::SetCameraPriority(int _Priority)
{
	CRenderMgr::GetInst()->RegisterCamera(this, _Priority);
}

void CCamera::LayerCheck(UINT _LayerIdx, bool _bCheck)
{
	if (_bCheck)
	{
		// _bCheck가 true라면 _LayerIdx를 왼쪽으로 한칸 옮기고 OR연산(하나라도 1이면 1반환)
		m_LayerCheck |= (1 << _LayerIdx);
	}
	else
	{
		// _bCheck가 false라면 _LayerIdx를 왼쪽으로 한칸 옮기고 반전시킨다음 AND연산(둘다 1이어야 반환)
		m_LayerCheck &= ~(1 << _LayerIdx);
	}
}

void CCamera::LayerCheck(const wstring& _strLayerName, bool _bCheck)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = pCurLevel->GetLayer(_strLayerName);

	if (nullptr == pLayer)
	{
		return;
	}

	int idx = pLayer->GetLayerIdx();
	LayerCheck(idx, _bCheck);
}