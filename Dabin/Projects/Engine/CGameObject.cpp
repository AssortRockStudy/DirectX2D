#include "pch.h"
#include "CGameObject.h"
#include "CComponent.h"
#include "CRenderComponent.h"
#include "CScript.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
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
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (m_arrCom[i])
			m_arrCom[i]->begin();
	}
}

void CGameObject::tick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (m_arrCom[i])
			m_arrCom[i]->tick();
	}
	for (size_t i = 0; i < m_vecScript.size(); ++i)
		m_vecScript[i]->tick();
}

void CGameObject::finaltick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (m_arrCom[i])
			m_arrCom[i]->finaltick();
	}
}

void CGameObject::render()
{
	if (m_RenderCom)
		m_RenderCom->render();
}

void CGameObject::DisconnectParent()
{
	vector<CGameObject*>::iterator iter = find(m_Parent->m_vecChild.begin(), m_Parent->m_vecChild.end(), this);
	if (iter != m_Parent->m_vecChild.end())
	{
		m_Parent->m_vecChild.erase(iter);
		m_Parent = nullptr;
		return;
	}

	// 부모가 없는 오브젝트에 호출했거나,
	// 부모는 자식을 가리키지 않는데, 자식은 부모를 가리키는 경우
	assert(nullptr);
}

void CGameObject::AddComponent(CComponent* _Component)
{
	COMPONENT_TYPE type = _Component->GetType();

	if (type == COMPONENT_TYPE::SCRIPT)
	{
		// type isn't script
		assert(dynamic_cast<CScript*>(_Component));
		m_vecScript.push_back((CScript*)_Component);
		_Component->m_Owner = this;
	}
	else
	{
		// already exist
		assert(m_arrCom[(UINT)type] == nullptr);
		m_arrCom[(UINT)type] = _Component;
		_Component->m_Owner = this;

		// render component
		CRenderComponent* tmp = dynamic_cast<CRenderComponent*>(_Component);
		if (tmp)
		{
			// already exist
			assert(m_RenderCom == nullptr);
			m_RenderCom = tmp;
		}
	}
}

void CGameObject::AddChild(CGameObject* _Child)
{
	if (_Child->m_Parent)
		_Child->DisconnectParent();

	_Child->m_Parent = this;
	m_vecChild.push_back(_Child);
}
