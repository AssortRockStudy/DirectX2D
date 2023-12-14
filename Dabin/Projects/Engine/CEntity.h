#pragma once

// =======================================
// CEntity: ��� GameObjects�� ����ϴ� �⺻ class
// =======================================

class CEntity
{
private:
	static UINT g_NextID;

	const UINT	m_ID;
	wstring		m_strName;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	UINT GetID() { return m_ID; }

public:
	CEntity();
	~CEntity();
};

