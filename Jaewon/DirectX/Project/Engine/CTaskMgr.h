#pragma once
#include "singleton.h"

enum class TASK_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	LEVEL_CHANGE,
	ADD_CHILD,
	DISCONNECT_PARENT,
};

struct FTask
{
	TASK_TYPE Type;
	UINT_PTR  Param_1;
	UINT_PTR  Param_2;
};

class CTaskMgr :
    public CSingleton<CTaskMgr>
{
	SINGLE(CTaskMgr);

private:
	vector<FTask>	m_vecTask;

public:
	void tick();
	void AddTask(const FTask& _Task){
		m_vecTask.push_back(_Task);
	}
};

