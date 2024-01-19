#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_Time(0.f)
	, m_DeltaTime(0.f)
	, m_iCall(0)
{	
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	QueryPerformanceFrequency(&m_Frequency);

	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_CurCount);

	m_DeltaTime = double(m_CurCount.QuadPart - m_PrevCount.QuadPart) / double(m_Frequency.QuadPart);

	m_PrevCount = m_CurCount;

	if ((1. / 60.) < m_DeltaTime)
		m_DeltaTime = (1. / 60.);


	m_Time += m_DeltaTime;
	if (1. <= m_Time)
	{
		wchar_t szText[50] = {};
		swprintf_s(szText, 50, L"DeltaTime : %f, FPS : %d", m_DeltaTime, m_iCall);
		SetWindowText(CEngine::GetInst()->GetMainWind(), szText);

		m_iCall = 0;
		m_Time = 0.f;
	}

	++m_iCall;

	g_global.g_dt = (float)m_DeltaTime;
	g_global.g_time += (float)m_DeltaTime;
}