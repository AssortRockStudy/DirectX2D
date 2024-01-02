#include "pch.h"
#include "CLayer.h"
#include "CGameObject.h"

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
		m_vecParent[i]->begin();
}

void CLayer::tick()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
		m_vecParent[i]->tick();
}

void CLayer::finaltick()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
		m_vecParent[i]->finaltick();
}

void CLayer::render()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
		m_vecObjects[i]->render();
}

void CLayer::AddObject(CGameObject* _Object, bool _bMove)
{
	if (nullptr == _Object->GetParent()){
		if (-1 != _Object->m_iLayerIdx)
			_Object->DisconnectWithLayer();

		m_vecParent.push_back(_Object);
	}
	list<CGameObject*> queue;
	queue.push_back(_Object);

	while (!queue.empty()){
		CGameObject* pObject = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pObject->m_vecChild.size(); ++i)
			queue.push_back(pObject->m_vecChild[i]);

		if (pObject == _Object)
			pObject->m_iLayerIdx = m_iLayerIdx;
		else{
			if (_bMove)
				pObject->m_iLayerIdx = m_iLayerIdx;
			else if (-1 == pObject->m_iLayerIdx)
				pObject->m_iLayerIdx = m_iLayerIdx;
		}
	}
}

void CLayer::DetachGameObject(CGameObject* _Object)
{
	assert(!(-1 == _Object->m_iLayerIdx || _Object->m_iLayerIdx != m_iLayerIdx));

	if (nullptr != _Object->GetParent())
		_Object->m_iLayerIdx = -1;

	else{
		vector<CGameObject*>::iterator iter = m_vecParent.begin();
		for (; iter != m_vecParent.end(); ++iter){
			if (*iter == _Object){
				m_vecParent.erase(iter);
				_Object->m_iLayerIdx = -1;
				return;
			}
		}
	}
	assert(nullptr);
}