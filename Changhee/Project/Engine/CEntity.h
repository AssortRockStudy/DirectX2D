#pragma once


class CEntity
{
private:
	static UINT g_NextID;

private:
	const UINT	m_iID;
	wstring		m_strName;

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	UINT GetID() { return m_iID; }

public:
	CEntity();
	virtual ~CEntity();
};

