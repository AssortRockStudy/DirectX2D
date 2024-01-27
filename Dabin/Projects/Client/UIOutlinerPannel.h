#pragma once
#include "UI.h"

class UIOutlinerPannel :
    public UI
{
public:
    virtual void render_update() override;

public:
    UIOutlinerPannel();
    ~UIOutlinerPannel();
};

