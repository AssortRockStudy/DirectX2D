#pragma once
#include "AssetUI.h"


class MaterialUI :
    public AssetUI
{
public:
    virtual void render_update() override;

public:
    MaterialUI();
    ~MaterialUI();
};

