#include "pch.h"
#include "CTaskMgr.h"
#include "CGameObject.h"
#include "CLevel.h"
#include "CLevelMgr.h"

CTaskMgr::CTaskMgr()
{

}

CTaskMgr::~CTaskMgr()
{

}

void CTaskMgr::tick()
{
	for (int i = 0; i < m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			// params
			int layerIdx = (int)m_vecTask[i].Param_1;
			CGameObject* pObj = (CGameObject*)m_vecTask[i].Param_2;

			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			pCurLevel->AddObject(pObj, layerIdx);

			/*
			* if (pCurLevel->GetState() == LEVEL_STATE::PLAY)
			*	Object->begin();
			*/
		}
			break;

		case TASK_TYPE::DELETE_OBJECT:
		{
			// params
			CGameObject* pDeadObj = (CGameObject*)m_vecTask[i].Param_1;

			list<CGameObject*>queue{ pDeadObj };
			while (!queue.empty())
			{
				CGameObject* pObj = queue.front();
				queue.pop_front();

				pObj->m_bDead = true;
				for (size_t i = 0; i < pObj->m_vecChild.size(); ++i)
					queue.push_back(pObj->m_vecChild[i]);	
			}
		}
			break;

		case TASK_TYPE::LEVEL_CHANGE:
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
