#include "pch.h"
#include "CEngine.h"

#include "CDevice.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

#include "test.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_vResolution()

{

}

CEngine::~CEngine()
{
	TestRelease();
}

int CEngine::Init(HWND hwnd, Vec2 _vResolution)
{
	//출력 윈도우
	m_hMainWnd = hwnd;

	//출력 해상도
	m_vResolution = _vResolution;

	//장치 초기화
	RECT rt = { 0, 0, (int)m_vResolution.x, (int)m_vResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainWnd, nullptr, 10.f, 10.f, rt.right - rt.left, rt.bottom - rt.top, 0);

	if(FAILED(CDevice::GetInst()->Init(m_hMainWnd, m_vResolution)))
	{
		MessageBox(nullptr, L"Device 초기화 실패", L"초기화 실패", MB_OK);
		return E_FAIL;
	}

	// Manager 초기화
	CPathMgr::init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();


	if (FAILED(TestInit()))
	{
		return E_FAIL;
	}


	return S_OK;
}

void CEngine::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();


	//TEST UPDATE
	TestProgress();
}
