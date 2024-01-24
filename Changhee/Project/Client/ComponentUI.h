#pragma once
#include "UI.h"

#include <Engine/CGameObject.h>

class ComponentUI :
    public UI
{
private:
    CGameObject*        m_TargetObject;
    COMPONENT_TYPE      m_Type;

    string              m_ComponentTitle;

public:
    virtual void render_update() override;

public:
    CGameObject* GetTargetObject() { return m_TargetObject; }
    COMPONENT_TYPE GetType() { return m_Type; }

    void SetTargetObject(CGameObject* _Target);
    void SetComponentTitle(const string& _Title) { m_ComponentTitle = _Title; }

public:
    ComponentUI(const string& _strName, const string& _ID, COMPONENT_TYPE _Type);
    ~ComponentUI();

};

