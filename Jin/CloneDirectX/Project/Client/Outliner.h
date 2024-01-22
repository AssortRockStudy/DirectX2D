#pragma once
#include "UI.h"

class Outliner :
    public UI
{
public:
    virtual void render_update() override;

public:
    Outliner();
    ~Outliner();
};

// 현재 레벨에 있는 모든 오브젝트들 나열하는..

