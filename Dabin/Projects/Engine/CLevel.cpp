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

void CLevel::clear()
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
		m_arrLayer[i]->m_vecObjects.clear();
}

void CLevel::begin()
{
	for (size_t i = 0; i < LAYER_MAX; ++i)
		m_arrLayer[i]->begin();
}

void CLevel::tick()
{
	for (size_t i = 0; i < LAYER_MAX; ++i)
		m_arrLayer[i]->tick();
}

void CLevel::finaltick()
{
	for (size_t i = 0; i < LAYER_MAX; ++i)
		m_arrLayer[i]->finaltick();
}

void CLevel::AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove)
{
	m_arrLayer[_LayerIdx]->AddObject(_Object, _bChildMove);
}

void CLevel::AddObject(CGameObject* _Object, const wstring& _LayerName, bool _bChildMove)
{
	CLayer* pLayer = GetLayer(_LayerName);
	if (!pLayer)
		return;

	pLayer->AddObject(_Object, _bChildMove);
}

CLayer* CLevel::GetLayer(const wstring& _strLayerName)
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		if (m_arrLayer[i]->GetName() == _strLayerName)
			return m_arrLayer[i];
	}
	return nullptr;
}

CGameObject* CLevel::FindObjectByName(const wstring& _strName)
{
	for (size_t i = 0; i < LAYER_MAX; ++i)
	{
		const vector<CGameObject*>& vecObject = m_arrLayer[i]->GetLayerObjects();
		for (size_t j = 0; j < vecObject.size(); ++j)
		{
			if (vecObject[j]->GetName() == _strName)
				return vecObject[j];
		}
	}
	return nullptr;
}

void CLevel::FindObjectsByName(const wstring& _strName, vector<CGameObject*>& _out)
{
	for (size_t i = 0; i < LAYER_MAX; ++i)
	{
		const vector<CGameObject*>& vecObject = m_arrLayer[i]->GetLayerObjects();
		for (size_t j = 0; j < vecObject.size(); ++j)
		{
			if (vecObject[j]->GetName() == _strName)
				_out.push_back(vecObject[j]);
		}
	}
}
