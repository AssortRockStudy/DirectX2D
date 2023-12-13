#pragma once

class CTimeMgr
	: public CSingleton<CTimeMgr>
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_Frequency;
	LARGE_INTEGER	m_PrevCount;
	LARGE_INTEGER	m_CurCount;
	float			m_fDeltaTime;


	UINT			m_iCall;
	float			m_fTime;

public:
	float GetDeltaTime() { return m_fDeltaTime; }

public:
	void init();
	void tick();
};

