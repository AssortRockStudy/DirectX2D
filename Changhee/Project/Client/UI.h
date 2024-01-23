#pragma once

#include "imgui.h"

class UI
{
private:
	string				m_strName;
	string				m_strID;
	bool				m_bActive;

	UI*					m_Parent;
	vector<UI*>			m_vecChildUI;

public:
	const string& GetName() { return m_strName; }
	const string& GetID() { return m_strID; }
	bool IsActivate() { return m_bActive; }
	UI* GetParentUI() { return m_Parent; }

	void SetName(const string& _Name) { m_strName = _Name; }
	void Activate() { m_bActive = true; }
	void Deactivate() { m_bActive = false; }


	void AddChildUI(UI* _ChildUI)
	{
		m_vecChildUI.push_back(_ChildUI);
		_ChildUI->m_Parent = this;
	}


public:
	virtual void tick();
	virtual void render();
	virtual void render_update() = 0;

public:
	UI(const string& _strName, const string& _strID);
	~UI();
};

