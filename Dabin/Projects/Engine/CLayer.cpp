#include "pch.h"
#include "CLayer.h"
#include "CGameObject.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
}

void CLayer::begin()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
		m_vecObj[i]->begin();
}

void CLayer::tick()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
		m_vecObj[i]->tick();
}

void CLayer::finaltick()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
		m_vecObj[i]->finaltick();
}

void CLayer::render()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
		m_vecObj[i]->render();
}
