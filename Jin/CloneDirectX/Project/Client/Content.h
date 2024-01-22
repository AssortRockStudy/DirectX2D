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

// AssetMgr 에 로딩되어 있는 모든 에셋들을 나열