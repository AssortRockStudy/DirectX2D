#pragma once
#include "UI.h"


class Content :
    public UI
{

public:
    virtual void render_update() override;

public:
    Content();
    ~Content();
};

