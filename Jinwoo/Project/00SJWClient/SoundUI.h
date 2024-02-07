#pragma once
#include "AssetUI.h"


class SoundUI :
    public AssetUI
{
public:
    virtual void render_update() override;

public:
    SoundUI();
    ~SoundUI();
};

