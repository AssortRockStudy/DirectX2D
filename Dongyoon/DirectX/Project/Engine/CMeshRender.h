#pragma once
#include "CRenderComponent.h"



class CMeshRender :
    public CRenderComponent
{

public:
    virtual void UpdateData() override;
    virtual void finaltick();
    virtual void render() override;

public:
    CMeshRender();
    ~CMeshRender();
};

