#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CRenderComponent.h"

#include "CScript.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CLayer.h"

#include "CGC.h"

CGameObject::CGameObject()
	: m_arrCom{}
	, m_RenderCom(nullptr)
	, m_Parent(nullptr)
	, m_iLayerIdx(-1) //��� ����(���̾�)���� �ҼӵǾ����� �ʴ´�. 
	, m_bDead(false)
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
		//�̹� �ش� Ÿ���� ������Ʈ�� ������ ���
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

			//�̹� �� ���� �̻��� RenderComponent�� �����ϰ� �ִ� ���
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

	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(m_iLayerIdx);
	pCurLayer->RegisterGameObject(this);

	vector<CGameObject*>::iterator iter = m_vecChild.begin();
	for (; iter != m_vecChild.end();)
	{
		(*iter)->finaltick();

		if ((*iter)->m_bDead)
		{
			CGC::GetInst()->Add(*iter);
			iter = m_vecChild.erase(iter);
		}
		else
		{
			++iter;
		}
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

	// �θ� ���� Obj�� �� �Լ��� ȣ���߰ų�
	// �θ�� �ڽ��� ����Ű�� ���� �ʴµ�, �ڽ��� �θ� ����Ű�� ���
	assert(nullptr);
}

void CGameObject::DisconnectWithLayer()
{
	if (m_iLayerIdx == -1)
		return;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pCurLayer = pCurLevel->GetLayer(m_iLayerIdx);
	pCurLayer->DetachGameObject(this);
}

void CGameObject::AddChild(CGameObject* _Child)
{
	if (_Child->m_Parent)
	{
		// ���� �θ� ������Ʈ�� ���� ����
		_Child->DisconnectWithParent();
	}

	// �θ� �ڽ� ����
	_Child->m_Parent = this;
	m_vecChild.push_back(_Child);
}

void CGameObject::Destroy()
{
	GamePlayStatic::DestroyGameObject(this);
}
