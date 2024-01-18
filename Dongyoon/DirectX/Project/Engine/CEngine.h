#pragma once


class CEngine
	: public CSingleton<CEngine>
{
	SINGLE(CEngine);

private:
	HWND	m_hMainWnd; // ���� ������ �ڵ�
	Vec2	m_vResolution; // �ػ� ����

public:
	HWND GetMainWind() { return m_hMainWnd; }

private:
	void DebugFunctionCheck();

public:
	int Init(HWND hwnd, Vec2 m_vResolution);
	void progress();


};

