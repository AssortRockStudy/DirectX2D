#pragma once
#include "UI.h"

#include <Engine\CGameObject.h>
#include <Engine\CAsset.h>

class TransformUI;

class Inspector :
    public UI
{
private:
    CGameObject*    m_TargetObject;
    Ptr<CAsset>     m_TargetAsset;

    TransformUI*    m_TransformUI;

public:
    void SetTaretObject(CGameObject* _Object);
    void SetTargetAsset(Ptr<CAsset> _Asset);

public:
    virtual void tick() override;
    virtual void render_update() override;

public:
    Inspector();
    ~Inspector();
};

