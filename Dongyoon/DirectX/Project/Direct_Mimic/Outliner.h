#pragma once
#include "UI.h"

//현재 레벨에 있는 모든 Object를 나열

class Outliner :
    public UI
{
public:
    virtual void render_update() override;

public:
    Outliner();
    ~Outliner();
};

