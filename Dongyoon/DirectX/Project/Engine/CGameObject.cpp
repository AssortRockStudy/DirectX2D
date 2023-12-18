#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CRenderComponent.h"



CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
{
}

CGameObject::~CGameObject()
{
	Delete_Array<CComponent, (UINT)COMPONENT_TYPE::END>(m_arrCom);
}

void CGameObject::AddComponent(CComponent* _Component)
{
	COMPONENT_TYPE type = _Component->GetType();

	m_arrCom[(UINT)type] = _Component;
	_Component->m_Owner = this;

	m_RenderCom = dynamic_cast<CRenderComponent*>(_Component);
}

void CGameObject::begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (m_arrCom[i] != nullptr)
		{
			m_arrCom[i]->begin();
		}
	}

}

void CGameObject::tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (m_arrCom[i] != nullptr)
		{
			m_arrCom[i]->tick();
		}
	}
}

void CGameObject::finaltick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (m_arrCom[i] != nullptr)
		{
			m_arrCom[i]->finaltick();
		}
	}
}

void CGameObject::render()
{
	if(m_RenderCom != nullptr)
	{ 
		m_RenderCom->render();
	}
}
