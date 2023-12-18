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
	Delete_Array<CComponent, (UINT)COMPONENT_TYPE::END>(m_arrCom);
}

void CGameObject::AddComponent(CComponent* _Component)
{
	COMPONENT_TYPE type = _Component->GetType();

	if (type == COMPONENT_TYPE::SCRIPT)
	{
		//이미 해당 타입의 컴포넌트를 보유한 경우
		assert(dynamic_cast<CScript*>(_Component));

		m_vecScript.push_back((CScript*)_Component);
		_Component->m_Owner = this;
	}
	else
	{
		assert(!m_arrCom[(UINT)type]);

		m_arrCom[(UINT)type] = _Component;
		_Component->m_Owner = this;

		CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Component);
		if (nullptr != pRenderCom)
		{

			//이미 한 종류 이상의 RenderComponent를 보유하고 있는 경우
			assert(!m_RenderCom);

			m_RenderCom = pRenderCom;
		}

	}


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

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->tick();
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
