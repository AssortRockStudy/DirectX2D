#pragma once
#include "UI.h"
#include <Engine/CGameObject.h>
#include <Engine/CAsset.h>
#include "TransformUI.h"

class Inspector :
    public UI
{
private:
    CGameObject* m_TargetObject;
    Ptr<CAsset> m_TargetAsset;
    TransformUI* m_TransformUI;

public:
    virtual void tick() override;
    virtual void render_update() override;

public:
    void SetTargetObject(CGameObject* _Object) { 
        m_TargetObject = _Object;
        m_TransformUI->SetTargetObject(_Object);
    }
    void SetTargetAsset(Ptr<CAsset> _Asset) { m_TargetAsset = _Asset; }

public:
    Inspector();
    ~Inspector();
};

