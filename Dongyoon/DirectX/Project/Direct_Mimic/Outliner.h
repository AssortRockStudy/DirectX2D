#pragma once
#include "UI.h"

//���� ������ �ִ� ��� Object�� ����

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

