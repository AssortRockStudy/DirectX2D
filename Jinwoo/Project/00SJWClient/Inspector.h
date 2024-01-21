#pragma once
#include "UI.h"

#include <Engine\CGameObject.h>
#include <Engine\CAsset.h>

class ComponentUI;

class Inspector :
    public UI
{
private:
    CGameObject*    m_TargetObject;
    Ptr<CAsset>     m_TargetAsset;

    ComponentUI*    m_arrComUI[(UINT)COMPONENT_TYPE::END];

public:
    void SetTaretObject(CGameObject* _Object);
    void SetTargetAsset(Ptr<CAsset> _Asset);

    CGameObject* GetTargetObject() { return m_TargetObject; }

public:
    virtual void tick() override;
    virtual void render_update() override;

public:
    Inspector();
    Inspector(string _strName, string _strID);
    ~Inspector();
};

