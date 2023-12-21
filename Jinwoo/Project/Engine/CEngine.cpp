#include "pch.h"
#include "CEngine.h"

#include "CDevice.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_vResolution()
{

}

CEngine::~CEngine()
{
	
}

int CEngine::init(HWND _hWnd, Vec2 _vResolution)
{
	m_hMainWnd = _hWnd;
	m_vResolution = _vResolution;

	RECT rt = { 0, 0, (int)m_vResolution.x, (int)m_vResolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);

	if (CDevice::GetInst()->init(m_hMainWnd, m_vResolution))
	{
		MessageBox(nullptr, L"CDevice 초기화 실패", L"초기화 실패", MB_OK);
		return E_FAIL;
	}

	// Manager Init
	CPathMgr::init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CAssetMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();

	return S_OK;
}

void CEngine::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();

	// Level Update
	CLevelMgr::GetInst()->tick();
	CLevelMgr::GetInst()->render();
}
