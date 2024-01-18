#pragma once


class CEngine
	: public CSingleton<CEngine>
{
	SINGLE(CEngine);

private:
	HWND	m_hMainWnd; // 메인 윈도우 핸들
	Vec2	m_vResolution; // 해상도 정보

public:
	HWND GetMainWind() { return m_hMainWnd; }

private:
	void DebugFunctionCheck();

public:
	int Init(HWND hwnd, Vec2 m_vResolution);
	void progress();


};

