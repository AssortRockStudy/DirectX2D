#pragma once
#include "ComponentUI.h"

#include <Engine\CGameObject.h>

class MeshRenderUI :
    public ComponentUI
{
public:
    virtual void render_update() override;

public:
    MeshRenderUI();
    ~MeshRenderUI();
};

