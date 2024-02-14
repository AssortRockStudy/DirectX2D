#pragma once
#include "UI.h"

class TreeUI;
class TreeNode;

class Outliner :
    public UI
{
private:
    TreeUI* m_Tree;

public:
    virtual void render_update() override;

public:
    void ResetCurrentLevel();

private:
    void AddObjectToTree(TreeNode* _Node, CGameObject* _Object);

public:
    Outliner();
    ~Outliner();

};

