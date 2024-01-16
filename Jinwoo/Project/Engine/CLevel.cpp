#include "pch.h"
#include "CLevel.h"

#include "CLayer.h"
#include "CGameObject.h"

CLevel::CLevel()
	: m_arrLayer{}
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i] = new CLayer;
		m_arrLayer[i]->m_iLayerIdx = i;
	}
}

CLevel::~CLevel()
{
	Delete_Array(m_arrLayer);
}

void CLevel::begin()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->begin();
	}
}

void CLevel::tick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->tick();
	}
}

void CLevel::finaltick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->finaltick();
	}
}

void CLevel::clear()
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->m_vecObjects.clear();
	}
}

void CLevel::AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove)
{
	m_arrLayer[_LayerIdx]->AddObject(_Object, _bChildMove);
}

void CLevel::AddObject(CGameObject* _Object, const wstring& _strLayerName, bool _bChildMove)
{
	CLayer* pLayer = GetLayer(_strLayerName);

	if (nullptr == pLayer)
	{
		return;
	}

	pLayer->AddObject(_Object, _bChildMove);
}


CLayer* CLevel::GetLayer(const wstring& _strLayerName)
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		if (_strLayerName == m_arrLayer[i]->GetName())
		{
			return m_arrLayer[i];
		}
	}

	return nullptr;
}

CGameObject* CLevel::FindObjectByName(const wstring& _strName)
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		const vector<CGameObject*>& vecParent = m_arrLayer[i]->GetParentObjects();

		for (size_t j = 0; j < vecParent.size(); ++j)
		{
			list<CGameObject*> queue;
			queue.push_back(vecParent[j]);

			// 레이어에 입력되는 오브젝트 포함, 그 밑에 달린 자식들까지 모두 확인
			while (!queue.empty())
			{
				CGameObject* pObject = queue.front();
				queue.pop_front();

				const vector<CGameObject*>& vecChild = pObject->GetChild();
				for (size_t k = 0; k < vecChild.size(); ++k)
				{
					queue.push_back(vecChild[k]);
				}

				if (_strName == pObject->GetName())
				{
					return pObject;
				}
			}
		}
	}

	return nullptr;
}

void CLevel::FindObjectsByName(const wstring& _strName, vector<CGameObject*>& _vecObj)
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		const vector<CGameObject*>& vecParent = m_arrLayer[i]->GetParentObjects();

		for (size_t j = 0; j < vecParent.size(); ++j)
		{
			list<CGameObject*> queue;
			queue.push_back(vecParent[j]);

			// 레이어에 입력되는 오브젝트 포함, 그 밑에 달린 자식들까지 모두 확인
			while (!queue.empty())
			{
				CGameObject* pObject = queue.front();
				queue.pop_front();

				const vector<CGameObject*>& vecChild = pObject->GetChild();
				for (size_t k = 0; k < vecChild.size(); ++k)
				{
					queue.push_back(vecChild[k]);
				}

				if (_strName == pObject->GetName())
				{
					_vecObj.push_back(pObject);
				}
			}
		}
	}
}
