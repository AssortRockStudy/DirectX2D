#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
CGameObject::CGameObject()
	: m_arrCom{}
{
}

CGameObject::~CGameObject()
{
	Delete_Array(m_arrCom);
}

void CGameObject::begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++) {
		if (nullptr != m_arrCom[i]) {
			m_arrCom[i]->begin();
		}
	}
}

void CGameObject::tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++) {
		if (nullptr != m_arrCom[i]) {
			m_arrCom[i]->tick();
		}
	}
}

void CGameObject::finaltick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++) {
		if (nullptr != m_arrCom[i]) {
			m_arrCom[i]->finaltick();
		}
	}
}

void CGameObject::render()
{
}

void CGameObject::AddComponent(CComponent* _Component)
{
	COMPONENT_TYPE type = _Component->GetType();

	m_arrCom[(UINT)type] = _Component;
	_Component->m_Owner = this;
}


