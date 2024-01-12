#pragma once
#include "CRenderComponent.h"

// =======================================
// CMeshRender: Mesh render 기능 담당
// =======================================

class CMeshRender :
    public CRenderComponent
{
public: 
    virtual void render() override;
    virtual void UpdatePipeline() override;

public:
    CMeshRender();
    ~CMeshRender();
};

