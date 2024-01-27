#pragma once
#include "UI.h"
#include "Engine/CGameObject.h"
#include "Engine/CAsset.h"
// =======================================
// InspectorPannel: gameobject가 가지는 component 연결해 띄우는 UI
// =======================================

class UIComponent;

class UIInspectorPannel :
    public UI
{
private:
    CGameObject*    m_TargetObject;
    Ptr<CAsset>     m_TargetAsset;
    UIComponent*    m_arrComp[(UINT)COMPONENT_TYPE::END];

public:
    virtual void tick() override;
    virtual void render_update() override;

public:
    void SetTargetObject(CGameObject* _Object);
    void SetTargetAsset(Ptr<CAsset> _Asset) { m_TargetAsset = _Asset; }
    CGameObject* GetTargetObject() { return m_TargetObject; }

public:
    UIInspectorPannel();
    ~UIInspectorPannel();
};

