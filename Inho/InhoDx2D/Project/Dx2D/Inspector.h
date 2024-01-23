#pragma once
#include "UI.h"

#include <Engine/CGameObject.h>
#include <Engine/CAsset.h>

class ComponentUI;

class Inspector :
    public UI
{
private:
    CGameObject* m_TargetObject;
    Ptr<CAsset> m_TargetAsset;

    ComponentUI* m_arrComUI[(UINT)COMPONENT_TYPE::END];

public:
    virtual void tick() override;
    virtual void render_update() override;

public:
    void SetTargetObject(CGameObject* _Object);
    void SetTargetAsset(Ptr<CAsset> _Asset);

public:
    Inspector();
    ~Inspector();
};

