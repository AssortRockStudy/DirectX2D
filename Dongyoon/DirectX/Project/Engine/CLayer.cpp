#include "pch.h"
#include "CLayer.h"

#include "CGameObject.h"
#include "CLayer.h"
#include "CGC.h"

CLayer::CLayer()
	: m_iLayerIdx(-1)
{

}

CLayer::~CLayer()
{
	Delete_Vec(m_vecParent);
}

void CLayer::begin()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
	{
		m_vecParent[i]->begin();
	}
}

void CLayer::tick()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
	{
		m_vecParent[i]->tick();
	}
}

void CLayer::finaltick()
{
	vector<CGameObject*>::iterator iter = m_vecParent.begin();

	for (; iter != m_vecParent.end();)
	{
		(*iter)->finaltick();

		if ((*iter)->IsDead())
		{
			CGC::GetInst()->Add(*iter);
			iter = m_vecParent.erase(iter);
		}
		else
		{
			++iter;
		}
	}


}

void CLayer::render()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->render();
	}
}


void CLayer::DetachGameObject(CGameObject* _Object)
{
	assert(!(_Object->m_iLayerIdx == -1 || _Object->m_iLayerIdx != m_iLayerIdx));

	//부모  obj 존재
	if (nullptr != _Object->GetParent())
	{
		_Object->m_iLayerIdx = -1;
	}
	else // 최상위 obj일때
	{
		vector<CGameObject*>::iterator iter = m_vecParent.begin();

		for (; iter != m_vecParent.end(); ++iter)
		{
			if (*iter == _Object)
			{
				m_vecParent.erase(iter);
				_Object->m_iLayerIdx = -1;
				return;
			}
		}
	}

	assert(nullptr);
}

void CLayer::AddObject(CGameObject* _Object, bool _bMove)
{
	// _bMove : true  - 레이어에 입력되는 Object가 자식이 있는 경우, 자식까지 모두 해당 레이어로 넘어온다.
	// _bMove : false - 레이어에 입력되는 Object의 자식은 해당 레이어로 같이 넘어오지 않는다. 단 자식오브젝트가 레이어 소속이 없는 경우(-1)에만 같이 변경한다.


	//최상위 부모 obj
	if (nullptr == _Object->GetParent())
	{
		//다른 layer 소속
		if (_Object->m_iLayerIdx != -1)
		{
			//기존 layer의 parent vec에서 제거
			_Object->DisconnectWithLayer();
		}

		m_vecParent.push_back(_Object);

	}

	//obj의 layer 소속을 현재 layer로 변경
	//자식 obj의 layer 소속을 변경
	list<CGameObject*> queue;
	queue.push_back(_Object);


	//레이어에 입력되는 obj 포함, 하위 자식 확인
	while (!queue.empty())
	{
		CGameObject* pObject = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pObject->m_vecChild.size(); i++)
		{
			queue.push_back(pObject->m_vecChild[i]);
		}
		
		//최초 입력 obj는 무조건 해당 layer 소속 변경
		if (pObject == _Object)
			pObject->m_iLayerIdx = m_iLayerIdx;
		else
		{
			//자식 obj는 move가 true인 경우, 부모를 따라서 해당 layer로 변경
			if (_bMove)
				pObject->m_iLayerIdx = m_iLayerIdx;
			//move가 false 이지만, 자식 obj의 layer가 -1(무소속)이라면 부모따라 변경
			else if (pObject->m_iLayerIdx == -1)
				pObject->m_iLayerIdx = m_iLayerIdx;
		}
	}

}
