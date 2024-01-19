#pragma once

class CTimeMgr
	: public CSingleton<CTimeMgr>
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_Frequency;
	LARGE_INTEGER	m_PrevCount;
	LARGE_INTEGER	m_CurCount;
	double			m_DeltaTime;


	UINT			m_iCall;
	double			m_Time;

public:
	float GetDeltaTime() { return (float)m_DeltaTime; }
	double GetDeltaTime_d() { return m_DeltaTime; }

public:
	void init();
	void tick();
};

