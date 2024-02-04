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
	FDebugShapeInfo info = {};
	info.ShapeType = DEBUG_SHAPE::RECT;
	info.matWorld = _WorldMat;
	info.vColor = _Color;
	info.bDepthTest = _bDepthTest;
	info.fDuration = _Duration;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void GamePlayStatic::DrawDebugRect(Vec3 _vWorldPos, Vec3 _vWorldScale, Vec3 _WorldRot, Vec3 _Color, bool _bDepthTest, float _Duration)
{
	FDebugShapeInfo info = {};
	info.ShapeType = DEBUG_SHAPE::RECT;
	info.vWorldPos = _vWorldPos;
	info.vWorldScale = _vWorldScale;
	info.vWorldRot = _WorldRot;
	info.matWorld = XMMatrixScaling(_vWorldScale.x, _vWorldScale.y, _vWorldScale.z)
		* XMMatrixRotationX(_WorldRot.x) * XMMatrixRotationY(_WorldRot.y) * XMMatrixRotationZ(_WorldRot.z)
		* XMMatrixTranslation(_vWorldPos.x, _vWorldPos.y, _vWorldPos.z);
	info.vColor = _Color;
	info.bDepthTest = _bDepthTest;
	info.fDuration = _Duration;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void GamePlayStatic::DrawDebugCircle(Vec3 _vWorldPos, float _fRadius, Vec3 _Color, bool _bDepthTest, float _Duration)
{
	FDebugShapeInfo info = {};
	info.ShapeType = DEBUG_SHAPE::CIRCLE;
	info.vWorldPos = _vWorldPos;
	info.vWorldScale = Vec3(_fRadius, _fRadius, 1.f);
	info.vWorldRot = Vector3();
	info.matWorld = XMMatrixScaling(info.vWorldScale.x, info.vWorldScale.y, info.vWorldScale.z)
		* XMMatrixRotationX(info.vWorldRot.x) * XMMatrixRotationY(info.vWorldRot.y) * XMMatrixRotationZ(info.vWorldRot.z)
		* XMMatrixTranslation(_vWorldPos.x, _vWorldPos.y, _vWorldPos.z);
	info.vColor = _Color;
	info.bDepthTest = _bDepthTest;
	info.fDuration = _Duration;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void GamePlayStatic::DrawDebugCross(Vec3 _vWorldPos, float _fScale, Vec3 _Color, bool _bDepthTest, float _Duration)
{
	FDebugShapeInfo info = {};
	info.ShapeType = DEBUG_SHAPE::CROSS;
	info.vWorldPos = _vWorldPos;
	info.vWorldScale = Vec3(_fScale);
	info.vWorldRot = Vec3();
	info.matWorld = XMMatrixScaling(info.vWorldScale.x, info.vWorldScale.y, info.vWorldScale.z)
		* XMMatrixRotationX(info.vWorldRot.x) * XMMatrixRotationY(info.vWorldRot.y) * XMMatrixRotationZ(info.vWorldRot.z)
		* XMMatrixTranslation(_vWorldPos.x, _vWorldPos.y, _vWorldPos.z);
	info.vColor = _Color;
	info.bDepthTest = _bDepthTest;
	info.fDuration = _Duration;

	CRenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void Vector3::ToDegree()
{
	x = (x / XM_PI) * 180.f;
	y = (y / XM_PI) * 180.f;
	z = (z / XM_PI) * 180.f;
}

void Vector3::ToRadian()
{
	x = (x / 180.f) * XM_PI;
	y = (y / 180.f) * XM_PI;
	z = (z / 180.f) * XM_PI;
}

string wstrToStr(const wstring& _wstr)
{
	return string(_wstr.begin(), _wstr.end());
}

wstring str2Wstr(const string& _str)
{
	return wstring(_str.begin(), _str.end());
}
