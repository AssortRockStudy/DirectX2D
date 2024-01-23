#pragma once
#include "ComponentUI.h"

#include <Engine\CGameObject.h>

class Animator2DUI :
    public ComponentUI
{
public:
    virtual void render_update() override;

public:
    Animator2DUI();
    ~Animator2DUI();
};

