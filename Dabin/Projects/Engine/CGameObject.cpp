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
