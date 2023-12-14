#include "pch.h"
#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CDevice.h"
#include "RenderingTest.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_vResolution()
{
}

CEngine::~CEngine()
{
	TestRelease();
}

int CEngine::init(HWND _hWnd, Vec2 _vResolution)
{
	m_hMainWnd = _hWnd;
	m_vResolution = _vResolution;

	// window size, position
	RECT rect = { 0, 0, (int)m_vResolution.x, (int)m_vResolution.y };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainWnd, nullptr, 10, 10, rect.right - rect.left, rect.bottom - rect.top, 0);
	
	// device init
	if (FAILED(CDevice::GetInst()->init(m_hMainWnd, m_vResolution)))
	{
		MessageBox(nullptr, L"Device 초기화 실패", L"초기화 실패", MB_OK);
		return E_FAIL;
	}

	// Manager init
	CPathMgr::init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	// rendering resource init
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

	// rendering
	TestProgress();
}
