#include "pch.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CDevice.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CLayer.h"
#include "CRenderMgr.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_ProjType(PROJ_TYPE::PERSEPECTIVE)
	, m_FOV(XM_PI / 2.f)	// 90도
	, m_Width(0.f)
	, m_Scale(1.f)
	, m_AspectRatio(1.f)
	, m_Far(10000.f)
	, m_LayerCheck(0)
{
	Vec2 vRes = CDevice::GetInst()->GetRenderResolution();
	m_AspectRatio = vRes.x / vRes.y;
}

CCamera::~CCamera()
{
}

void CCamera::finaltick()
{
	// camera finaltick: view matrix와 projection matrix 계산

	// view matrix
	Vec3 vCamPos = Transform()->GetRelativePos();
	Vec3 vRight = Transform()->GetLocalDir(DIR_TYPE::RIGHT);
	Vec3 vUp	= Transform()->GetLocalDir(DIR_TYPE::UP);
	Vec3 vFront = Transform()->GetLocalDir(DIR_TYPE::FRONT);

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
}


void CCamera::render()
{
	// 계산한 view 행렬과 proj 행렬을 전역변수에 담아둔다.
	g_Transform.matView = m_matView;
	g_Transform.matProj = m_matProj;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	for (int i = 0; i < LAYER_MAX; ++i)
	{
		// 카메라가 찍도록 설정된 Layer 가 아니면 무시
		if (false == (m_LayerCheck & (1 << i)))
			continue;

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
		m_LayerCheck |= (1 << _LayerIdx);
	else
		m_LayerCheck &= ~(1 << _LayerIdx);
}

void CCamera::LayerCheck(const wstring& _strLayerName, bool _bCheck)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = pCurLevel->GetLayer(_strLayerName);
	if (!pLayer)
		return;

	int idx = pLayer->GetLayerIdx();
	LayerCheck(idx, _bCheck);
}
