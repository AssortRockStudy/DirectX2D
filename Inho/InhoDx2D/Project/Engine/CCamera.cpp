#include "pch.h"
#include "CCamera.h"

#include "CDevice.h"
#include "CTransform.h"

#include "CRenderMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CRenderComponent.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_ProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_FOV(XM_PI/2.f)
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
	Vec3 vCamPos = Transform()->GetRelativePos();
	Matrix matTrans = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);

	Vec3 vRight		= Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	Vec3 vUp			= Transform()->GetWorldDir(DIR_TYPE::UP);
	Vec3 vFront		= Transform()->GetWorldDir(DIR_TYPE::FRONT);

	Matrix matRotate = XMMatrixIdentity();
	matRotate._11 = vRight.x;		matRotate._12 = vUp.x;		matRotate._13 = vFront.x;
	matRotate._21 = vRight.y;		matRotate._22 = vUp.y;		matRotate._23 = vFront.y;
	matRotate._31 = vRight.z;		matRotate._32 = vUp.z;		matRotate._33 = vFront.z;

	m_matView = matTrans * matRotate;

	m_matProj = XMMatrixIdentity();

	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType) {
		Vec2 vResol = CDevice::GetInst()->GetRenderResolution();
		m_matProj = XMMatrixOrthographicLH(vResol.x * m_Scale, (vResol.x / m_AspectRatio) * m_Scale, 1.f, m_Far);
	}
	else {
		m_matProj = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, 1.f, m_Far);
	}

	g_Transform.matView = m_matView;
	g_Transform.matProj = m_matProj;

}

void CCamera::SetCameraPriority(int _Priority)
{
	CRenderMgr::GetInst()->RegisterCamera(this, _Priority);
}

void CCamera::LayerCheck(UINT _LayerIdx, bool _bCheck)
{
	if (_bCheck) {
		m_LayerCheck |= (1 << _LayerIdx);
	}
	else {
		m_LayerCheck &= ~(1 << _LayerIdx);
	}
}

void CCamera::LayerCheck(const wstring& _strLayerName, bool _bCheck)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = pCurLevel->GetLayer(_strLayerName);

	if (nullptr == pLayer)
		return;

	int idx = pLayer->GetLayerIdx();
	LayerCheck(idx, _bCheck);
}

void CCamera::SortObject()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	for (int i = 0; i < LAYER_MAX; i++) {
		if(false == (m_LayerCheck & (1 << i)))
			continue;
		CLayer* pLayer = pCurLevel->GetLayer(i);
		const vector<CGameObject*>& vecObjects = pLayer->GetLayerObjects();
		for (size_t j = 0; j < vecObjects.size(); j++) {
			CRenderComponent* renCom = vecObjects[j]->GetRenderComponent();
			if (!(renCom && renCom->GetMesh().Get() 
					&& renCom->GetMaterial().Get()
					&& renCom->GetMaterial()->GetShader().Get())){
				continue;
			}

			SHADER_DOMAIN domain = vecObjects[j]->GetRenderComponent()->GetMaterial()->GetShader()->GetDomain();

			switch (domain)
			{
			case SHADER_DOMAIN::DOMAIN_OPAQUE:
				m_vecOpaque.push_back(vecObjects[j]);
				break;
			case SHADER_DOMAIN::DOMAIN_MASKED:
				m_vecMasked.push_back(vecObjects[j]);
				break;
			case SHADER_DOMAIN::DOMAIN_TRANSPARENT:
				m_vecTransparent.push_back(vecObjects[j]);
				break;
			case SHADER_DOMAIN::DOMAIN_POSTPROCESS:
				m_vecPostProcess.push_back(vecObjects[j]);
				break;
			case SHADER_DOMAIN::DOMAIN_DEBUG:
				break;
			default:
				break;
			}
		}
	}
}

void CCamera::render()
{
	g_Transform.matView = m_matView;
	g_Transform.matProj = m_matProj;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	render(m_vecOpaque);
	render(m_vecMasked);
	render(m_vecTransparent);
	render(m_vecPostProcess);
}

void CCamera::render(vector<CGameObject*>& _vecObj)
{
	for (size_t i = 0; i < _vecObj.size(); i++) {
		_vecObj[i]->render();
	}

	_vecObj.clear();
}
