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

	//�θ�  obj ����
	if (nullptr != _Object->GetParent())
	{
		_Object->m_iLayerIdx = -1;
	}
	else // �ֻ��� obj�϶�
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
	// _bMove : true  - ���̾ �ԷµǴ� Object�� �ڽ��� �ִ� ���, �ڽı��� ��� �ش� ���̾�� �Ѿ�´�.
	// _bMove : false - ���̾ �ԷµǴ� Object�� �ڽ��� �ش� ���̾�� ���� �Ѿ���� �ʴ´�. �� �ڽĿ�����Ʈ�� ���̾� �Ҽ��� ���� ���(-1)���� ���� �����Ѵ�.


	//�ֻ��� �θ� obj
	if (nullptr == _Object->GetParent())
	{
		//�ٸ� layer �Ҽ�
		if (_Object->m_iLayerIdx != -1)
		{
			//���� layer�� parent vec���� ����
			_Object->DisconnectWithLayer();
		}

		m_vecParent.push_back(_Object);

	}

	//obj�� layer �Ҽ��� ���� layer�� ����
	//�ڽ� obj�� layer �Ҽ��� ����
	list<CGameObject*> queue;
	queue.push_back(_Object);


	//���̾ �ԷµǴ� obj ����, ���� �ڽ� Ȯ��
	while (!queue.empty())
	{
		CGameObject* pObject = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pObject->m_vecChild.size(); i++)
		{
			queue.push_back(pObject->m_vecChild[i]);
		}
		
		//���� �Է� obj�� ������ �ش� layer �Ҽ� ����
		if (pObject == _Object)
			pObject->m_iLayerIdx = m_iLayerIdx;
		else
		{
			//�ڽ� obj�� move�� true�� ���, �θ� ���� �ش� layer�� ����
			if (_bMove)
				pObject->m_iLayerIdx = m_iLayerIdx;
			//move�� false ������, �ڽ� obj�� layer�� -1(���Ҽ�)�̶�� �θ���� ����
			else if (pObject->m_iLayerIdx == -1)
				pObject->m_iLayerIdx = m_iLayerIdx;
		}
	}

}
