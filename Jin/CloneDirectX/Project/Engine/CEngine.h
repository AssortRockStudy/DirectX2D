#pragma once

class CEngine : public CSingleton<CEngine>
{
	SINGLETON(CEngine);

private:
	HWND		m_hMainWnd;		// ���� ������ �ڵ�
	Vec2		m_vResolution;			// �ػ� ����

public:
	int init(HWND _hWnd, Vec2 _vResolution);
	void progress(); // �� �����Ӹ��� ȣ���
};

