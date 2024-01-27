#pragma once
#include "UI.h"

class UIContentPannel :
    public UI
{
public:
    virtual void render_update() override;

public:
    UIContentPannel();
    ~UIContentPannel();
};

