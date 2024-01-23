#pragma once


class UI
{
private:
	string m_strName;
	string m_strID;

public:
	void SetName(const string& _Name) { m_strName = _Name; }
	const string& GetName() { return m_strName; }

public:
	UI();
	~UI();
};

