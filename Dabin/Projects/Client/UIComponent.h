#pragma once
#include "UI.h"
// =======================================
// UIComponent: Inspector�� Component�� ����ϴ� Parent UI
// =======================================

class UIInspectorPannel;

class UIComponent :
    public UI
{
private:
    UIInspectorPannel*  m_pInspector;
    COMPONENT_TYPE      m_Type;
    string              m_ComponentTitle;

public:
    virtual void render() override;
    virtual void render_update() override;
    void DecideActivation();

public:
    void SetInspector(UIInspectorPannel* _pInspector) { m_pInspector = _pInspector; }
    void SetTitle(const string& _title) { m_ComponentTitle = _title; }
    UIInspectorPannel* GetInspector() { return m_pInspector; }
    COMPONENT_TYPE GetType() { return m_Type; }

public:
    UIComponent(const string& _strName, const string& _ID, COMPONENT_TYPE _Type);
    ~UIComponent();
};

