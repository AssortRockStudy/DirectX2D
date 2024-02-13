#pragma once
#include "UI.h"

class TreeUI;

class Content :
    public UI
{
private:
    TreeUI* m_Tree;


public:
    void ResetContent();
    virtual void render_update() override;

public:
    Content();
    ~Content();
};

