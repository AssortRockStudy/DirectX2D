#include "pch.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_fTime(0.f)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// �ʴ� ��
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::tick()
{
	// Update DT
	QueryPerformanceCounter(&m_CurCount);
	m_DeltaTime = float(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)m_Frequency.QuadPart;
	m_PrevCount = m_CurCount;

	// DT ����
	if ((1.f / 60.f) < m_DeltaTime)
		m_DeltaTime = (1.f / 60.f);

	// 1 tick
	m_fTime += m_DeltaTime;
	if (m_fTime >= 1.f)
	{
		wchar_t szText[50] = {};
		swprintf_s(szText, 50, L"DeltaTime : %f, FPS : %d", m_DeltaTime, m_iCall);
		SetWindowText(CEngine::GetInst()->GetMainWind(), szText);

		m_iCall = 0;
		m_fTime = 0.f;
	}

	++m_iCall;

	g_Global.g_dt = m_DeltaTime;
	g_Global.g_time += m_DeltaTime;
}
