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
	//��� ������
	m_hMainWnd = hwnd;

	//��� �ػ�
	m_vResolution = _vResolution;

	//��ġ �ʱ�ȭ
	RECT rt = { 0, 0, (int)m_vResolution.x, (int)m_vResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainWnd, nullptr, 10.f, 10.f, rt.right - rt.left, rt.bottom - rt.top, 0);

	if(FAILED(CDevice::GetInst()->Init(m_hMainWnd, m_vResolution)))
	{
		MessageBox(nullptr, L"Device �ʱ�ȭ ����", L"�ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// Manager �ʱ�ȭ
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
