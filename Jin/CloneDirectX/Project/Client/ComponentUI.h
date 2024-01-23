#pragma once
#include "UI.h"

#include <Engine/CGameObject.h>

class ComponentUI :
    public UI
{
private:
    CGameObject* m_TargetObject;
    COMPONENT_TYPE  m_Type;

    string          m_ComponentTitle;

public:
    CGameObject* GetTargetObject() { return m_TargetObject; }
    void SetTargetObject(CGameObject* _Target);
    void SetComopnentTitle(const string& _title) { m_ComponentTitle = _title; }
    COMPONENT_TYPE GetType() { return m_Type; }

public:
    virtual void render_update() override;
public:
    ComponentUI(const string& _strName, const string& _ID, COMPONENT_TYPE _Type);
    ~ComponentUI();
};

