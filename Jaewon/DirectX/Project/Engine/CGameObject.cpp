#include "pch.h"
#include "CGameObject.h"
#include "CComponent.h"
#include "CRenderComponent.h"
#include "CScript.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_iLayerIdx(-1)
{
}

CGameObject::~CGameObject()
{
	Delete_Array(m_arrCom);
	Delete_Vec(m_vecScript);
	Delete_Vec(m_vecChild);
}

void CGameObject::begin()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i){
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->begin();
	}
	for (size_t i = 0; i < m_vecChild.size(); ++i)
		m_vecChild[i]->begin();
}

void CGameObject::tick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i){
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->tick();
	}
	for (size_t i = 0; i < m_vecScript.size(); ++i)
		m_vecScript[i]->tick();
	for (size_t i = 0; i < m_vecChild.size(); ++i)
		m_vecChild[i]->tick();
}

void CGameObject::finaltick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i){
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->finaltick();
	}

	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(m_iLayerIdx);
	pCurLayer->RegisterGameObject(this);

	for (size_t i = 0; i < m_vecChild.size(); ++i)
		m_vecChild[i]->finaltick();
}

void CGameObject::render()
{
	if (nullptr != m_RenderCom)
		m_RenderCom->render();
	for (size_t i = 0; i < m_vecChild.size(); ++i)
		m_vecChild[i]->render();
}

void CGameObject::AddComponent(CComponent* _Comonent)
{
	COMPONENT_TYPE type = _Comonent->GetType();
	if (type == COMPONENT_TYPE::SCRIPT){
		assert(dynamic_cast<CScript*>(_Comonent));
		m_vecScript.push_back((CScript*)_Comonent);
		_Comonent->m_Owner = this;
	}
	else{
		assert(!m_arrCom[(UINT)type]);

		m_arrCom[(UINT)type] = _Comonent;
		_Comonent->m_Owner = this;

		CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Comonent);
		if (nullptr != pRenderCom){
			assert(!m_RenderCom);
			m_RenderCom = pRenderCom;
		}
	}
}

void CGameObject::DisconnectWithParent()
{
	vector<CGameObject*>::iterator iter = m_Parent->m_vecChild.begin();
	for (; iter != m_Parent->m_vecChild.end(); ++iter){
		if (*iter == this){
			m_Parent->m_vecChild.erase(iter);
			m_Parent = nullptr;
			return;
		}
	}
	// �θ� ���� ������Ʈ�� DisconnectWithParent �Լ��� ȣ�� �߰ų�
	// �θ�� �ڽ��� ����Ű���� �ʰ� �ִµ�, �ڽ��� �θ� ����Ű�� �ִ� ���
	assert(nullptr);
}

void CGameObject::DisconnectWithLayer()
{
	if (-1 == m_iLayerIdx)
		return;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pCurLayer = pCurLevel->GetLayer(m_iLayerIdx);
	pCurLayer->DetachGameObject(this);
}

void CGameObject::AddChild(CGameObject* _Child)
{
	if (_Child->m_Parent)
		// ���� �θ� ������Ʈ�� ���� ����
		_Child->DisconnectWithParent();

	// �θ� �ڽ� ����
	_Child->m_Parent = this;
	m_vecChild.push_back(_Child);
}