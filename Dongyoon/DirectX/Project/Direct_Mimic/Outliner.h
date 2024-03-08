#pragma once
#include "UI.h"

//현재 레벨에 있는 모든 Object를 나열

class TreeUI;

class Outliner :
    public UI
{
private:
    TreeUI*     m_Tree;

public:
    virtual void render_update() override;

public:
    Outliner();
    ~Outliner();
};

