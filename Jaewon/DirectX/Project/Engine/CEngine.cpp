#include "pch.h"
#include "CEngine.h"
#include "CDevice.h"
#include "Test.h"
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
	SetWindowPos(m_hMainWnd, nullptr, 10.f, 10.f, rt.right - rt.left, rt.bottom - rt.top, 0);

	if (FAILED(CDevice::GetInst()->init(m_hMainWnd, m_vResolution)))
	{
		MessageBox(nullptr, L"Device �ʱ�ȭ ����", L"�ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	CPathMgr::init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CAssetMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();

	if (FAILED(TestInit()))
		return E_FAIL;

	return S_OK;
}

void CEngine::progress()
{
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	
	CLevelMgr::GetInst()->tick();
	CLevelMgr::GetInst()->render();
}