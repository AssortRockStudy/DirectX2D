#include "pch.h"
#include "CTaskMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGameObject.h"
#include "CComponent.h"

CTaskMgr::CTaskMgr(){}

CTaskMgr::~CTaskMgr() {}

void CTaskMgr::tick() {
	for (size_t i = 0; i < m_vecTask.size(); i++) {

		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::CREATE_OBJECT:

		{
			int LayerIdx = (int)m_vecTask[i].Param_1;
			CGameObject* Object = (CGameObject*)m_vecTask[i].Param_2;

			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			pCurLevel->AddObject(Object, LayerIdx, true);

			break;
		}

		case TASK_TYPE::DELETE_OBJECT:
			break;
		case TASK_TYPE::ADD_CHILD:
			break;
		case TASK_TYPE::DISCONNECT_PARENT:
			break;
		default:
			break;
		}

	}

	m_vecTask.clear();
}