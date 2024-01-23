#pragma once

#include "imgui.h"

class UI
{
private:
	string	m_strName;
	string	m_strID;
	ImVec2	m_vSize;
	bool	m_bActive;

	UI*		m_Parent;
	vector<UI*>	m_vecChildUI;

public:
	void SetName(const string& _name) { m_strName = _name; }
	const string& GetName() { return m_strName; }
	const string& GetID() { return m_strID; }

	void SetSize(ImVec2 _Size) { m_vSize = _Size; }
	ImVec2 GetSize() { return m_vSize; }

	void Activate() { m_bActive = true; }
	void Deactivate() { m_bActive = false; }
	bool IsActivate() { return m_bActive; }

	void AddChildUI(UI* _ChildUI)
	{
		m_vecChildUI.push_back(_ChildUI);
		_ChildUI->m_Parent = this;
	}

	UI* GetParentUI() { return m_Parent; }

public:
	virtual void tick();
	virtual void render();
	virtual void render_update() = 0;
public:
	UI(const string& _strName, const string& _strID);
	virtual ~UI();
};

