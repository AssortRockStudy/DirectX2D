#include "pch.h"
#include "CTaskMgr.h"
#include "CRenderMgr.h"

void GamePlayStatic::SpawnGameObject(CGameObject* _Target, int _LayerIdx)
{
	FTask task = {};
	task.Type = TASK_TYPE::CREATE_OBJECT;
	task.Param_1 = (DWORD_PTR)_LayerIdx; //WORD: CPU가 한번에 처리할 수 있는 데이터의 크기 단위 (유지보수 문제로 OS와 관계없이 16bit로 유지)
	task.Param_2 = (DWORD_PTR)_Target;
	CTaskMgr::GetInst()->AddTask(task);
}

void GamePlayStatic::DestroyGameObject(CGameObject* _Target)
{
	FTask task = {};
	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param_1 = (DWORD_PTR)_Target;
	CTaskMgr::GetInst()->AddTask(task);
}

void GamePlayStatic::DrawDebugRect(const Matrix& _WorldMat, Vec3 _Color, bool _bDepthTest, float _Duration)
{
	tDebugShapeInfo info = {};
	info.ShapeType = DEBUG_SHAPE::RECT;
	info.matWorld = _WorldMat;
	info.vColor = _Color;
	info.bDepthTest = _bDepthTest;
	info.fDuration = _Duration;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void GamePlayStatic::DrawDebugRect(Vec3 _vWorldPos, Vec3 _vWorldScale, Vec3 _WorldRot, Vec3 _Color, bool _bDepthTest, float _Duration)
{
	Matrix mat = XMMatrixScaling(_vWorldScale.x, _vWorldScale.y, _vWorldScale.z)
		* XMMatrixRotationX(_WorldRot.x) * XMMatrixRotationY(_WorldRot.y) * XMMatrixRotationZ(_WorldRot.z)
		* XMMatrixTranslation(_vWorldPos.x, _vWorldPos.y, _vWorldPos.z);
	
	DrawDebugRect(mat, _Color, _bDepthTest, _Duration);
}
