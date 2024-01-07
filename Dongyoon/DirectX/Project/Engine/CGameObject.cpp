#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CRenderComponent.h"

#include "CScript.h"


CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
{
}

CGameObject::~CGameObject()
{
	Delete_Array<CComponent, (UINT)COMPONENT_TYPE::END>(m_arrCom);
	Delete_Vec(m_vecScript);
	Delete_Vec(m_vecChild);
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

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->begin();
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
	
	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->tick();
	}
}

void CGameObject::finaltick()
{
	for (UINT i = 0; i < UINT(COMPONENT_TYPE::END); ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			m_arrCom[i]->finaltick();
		}
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->finaltick();
	}
}

void CGameObject::render()
{
	if(m_RenderCom != nullptr)
	{ 
		m_RenderCom->render();
	}

	for (size_t i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->render();
	}
}


void CGameObject::DisconnectWithParent()
{
	vector<CGameObject*>::iterator iter = m_Parent->m_vecChild.begin();

	for (; iter != m_Parent->m_vecChild.end(); ++iter)
	{
		if (*iter == this) 
		{
			m_Parent->m_vecChild.erase(iter);
			m_Parent = nullptr;
			return;
		}
	}

	// 부모가 없는 Obj에 이 함수를 호출했거나
	// 부모는 자식을 가리키고 있지 않는데, 자식은 부모를 가리키는 경우
	assert(nullptr);
}

void CGameObject::AddChild(CGameObject* _Child)
{
	if (_Child->m_Parent)
	{
		// 이전 부모 오브젝트랑 연결 해제
		_Child->DisconnectWithParent();
	}

	// 부모 자식 연결
	_Child->m_Parent = this;
	m_vecChild.push_back(_Child);
}